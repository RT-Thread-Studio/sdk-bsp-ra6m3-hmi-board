/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-04-07     yans       the first version
 */
#include <stdlib.h>
#include <sched.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <pthread.h>
#include <math.h>

#include "osal.h"
#include "ethercattype.h"
#include "nicdrv.h"
#include "ethercatbase.h"
#include "ethercatmain.h"
#include "ethercatdc.h"
#include "ethercatcoe.h"
#include "ethercatfoe.h"
#include "ethercatconfig.h"
#include "ethercatprint.h"
#include "ethercat.h"

#include "ui.h"

#define DBG_TAG "Master"
#define DBG_LVL DBG_INFO
#include "rtdbg.h"

#define EC_TIMEOUTMON   500

int active_master(void);
void turn_on(void);
void turn_off(void);
static void textarea_update_cb(void * user_data);
void update_textarea(lv_obj_t * ta, int32_t value);
static void chart_update_cb(void * user_data);
void update_chart(lv_obj_t * chart, lv_chart_series_t * series, int16_t value);

//pdo of csp mode
typedef struct PACKED{
    uint16 ControlWord;
    uint16 MaxTorque;
    int32 TargetPosition;
    int32 PositionOffset;
    int32 VelocityOffset;
    int16 TorqueOffset;
    uint16 TouchProbeFunction;
    uint16 PositiveTorqueLimitValue;
    uint16 NegativeTorqueLimitValue;
    uint32 DigitalOutputs;
} CSP_Output;

typedef struct PACKED{
    uint16 ErrorCode;
    uint16 StatusWord;
    int32 ActualPosition;
    int32 ActualVelocity;
    int16 ActualTorque;
    uint16 TouchProbeStatus;
    int32 TouchProbePosition1PositiveValue;
    int32 TouchProbePosition2PositiveValue;
    int32 FollowingErrorActualValue;
    uint32 DigitalInputs;
} CSP_Input;

//pdo of csv mode
typedef struct PACKED{
    uint16 ControlWord;
    uint16 MaxTorque;
    int32 VelocityOffset;
    int16 TorqueOffset;
    uint16 TouchProbeFunction;
    uint16 PositiveTorqueLimitValue;
    uint16 NegativeTorqueLimitValue;
    uint32 DigitalOutputs;
    int32 TargetVelocity;
} CSV_Output;

typedef struct PACKED{
    uint16 ErrorCode;
    uint16 StatusWord;
    int32 ActualPosition;
    int32 ActualVelocity;
    int16 ActualTorque;
    uint16 TouchProbeStatus;
    int32 TouchProbePosition1PositiveValue;
    int32 TouchProbePosition2PositiveValue;
    uint32 DigitalInputs;
} CSV_Input;

typedef struct {
    lv_obj_t * ta;
    char text[16];
} textarea_update_t;

typedef struct {
    lv_obj_t * chart;
    lv_chart_series_t * series;
    int16_t value;
} chart_update_t;

static char IOmap[1024];
volatile rt_uint8_t mode = 0;
static uint8 slave = 1;
rt_thread_t thread1;
rt_thread_t thread2;
int expectedWKC;
static volatile boolean inOP;
static volatile boolean master_state;
volatile int wkc;
uint8 currentgroup = 0;

CSP_Output *csp_outputs;
CSP_Input *csp_inputs;
CSV_Output *csv_outputs;
CSV_Input *csv_inputs;
uint16 cur_status;

#define OUTPUT(x, y)    mode == 0 ? (csp_outputs->x = y) : (csv_outputs->x = y)
#define INPUT(x)        mode == 0 ? (csp_inputs->x) : (csv_inputs->x)

#define __is_print(ch) ((unsigned int)((ch) - ' ') < 127u - ' ')

static void hex_dump(char *ptr, rt_size_t buflen)
{
    unsigned char *buf = (unsigned char *) ptr;
    int i, j;

    RT_ASSERT(ptr != RT_NULL);

    for (i = 0; i < buflen; i += 16)
    {
        rt_kprintf("%08X: ", i);

        for (j = 0; j < 16; j++)
            if (i + j < buflen)
                rt_kprintf("%02X ", buf[i + j]);
            else
                rt_kprintf("   ");
        rt_kprintf(" ");

        for (j = 0; j < 16; j++)
            if (i + j < buflen)
                rt_kprintf("%c", __is_print(buf[i + j]) ? buf[i + j] : '.');
        rt_kprintf("\n");
    }
}

void view_slave_data()
{
    hex_dump(IOmap, 32);
}

void echo_time(void)
{
    struct timeval tp;
    //osal_gettimeofday(&tp, 0);
    gettimeofday(&tp, 0);
    int a, b, c;
    a = tp.tv_sec;
    b = tp.tv_usec / 1000;
    c = tp.tv_usec % 1000;
    printf("****cur time = %d,%03d,%03d(us)\r\n", a, b, c);
}

static int drive_write8(uint16 slave, uint16 index, uint8 subindex, uint8 value)
{
    wkc = ec_SDOwrite(slave, index, subindex, FALSE, sizeof(value), &value, EC_TIMEOUTRXM);

    if (wkc <= 0)
        LOG_W("Slave %d write 0x%04X->0x%02X with 0x%02X       failed.", slave, index, subindex, value);
    else
        LOG_D("Slave %d write 0x%04X->0x%02X with 0x%02X       success.", slave, index, subindex, value);

    return wkc;
}

static int drive_write16(uint16 slave, uint16 index, uint8 subindex, uint16 value)
{
    wkc = ec_SDOwrite(slave, index, subindex, FALSE, sizeof(value), &value, EC_TIMEOUTRXM);

    if (wkc <= 0)
        LOG_W("Slave %d write 0x%04X->0x%02X with 0x%04X     failed.", slave, index, subindex, value);
    else
        LOG_D("Slave %d write 0x%04X->0x%02X with 0x%04X     success.", slave, index, subindex, value);

    return wkc;
}

__attribute__((unused)) static int drive_write32(uint16 slave, uint16 index, uint8 subindex, int32 value)
{
    wkc = ec_SDOwrite(slave, index, subindex, FALSE, sizeof(value), &value, EC_TIMEOUTRXM);

    if (wkc <= 0)
        LOG_W("Slave %d write 0x%04X->0x%02X with 0x%08X failed.", slave, index, subindex, value);
    else
        LOG_D("Slave %d write 0x%04X->0x%02X with 0x%08X success.", slave, index, subindex, value);

    return wkc;
}

void show_slave_info()
{
    for (int cnt = 1; cnt <= ec_slavecount; cnt++)
    {
        printf(
                "\nSlave:%d\n Name:%s\n Output size: %dbits\n Input size: %dbits\n State: %d\n Delay: %"LV_PRId32"[ns]\n Has DC: %d\n",
                cnt, ec_slave[cnt].name, ec_slave[cnt].Obits, ec_slave[cnt].Ibits, ec_slave[cnt].state,
                ec_slave[cnt].pdelay, ec_slave[cnt].hasdc);
        printf(" Activeports:%d.%d.%d.%d\n", (ec_slave[cnt].activeports & 0x01) > 0 ,
                (ec_slave[cnt].activeports & 0x02) > 0 ,
                (ec_slave[cnt].activeports & 0x04) > 0 ,
                (ec_slave[cnt].activeports & 0x08) > 0 );
        printf(" Configured address: %x\n", ec_slave[cnt].configadr);
        printf(" Outputs address: %p\n", ec_slave[cnt].outputs);
        printf(" Inputs address: %p\n", ec_slave[cnt].inputs);

        for (int j = 0; j < ec_slave[cnt].FMMUunused; j++)
        {
            printf(" FMMU%1d Ls:%x Ll:%4d Lsb:%d Leb:%d Ps:%x Psb:%d Ty:%x Act:%x\n", j,
                    (int) ec_slave[cnt].FMMU[j].LogStart, ec_slave[cnt].FMMU[j].LogLength,
                    ec_slave[cnt].FMMU[j].LogStartbit, ec_slave[cnt].FMMU[j].LogEndbit,
                    ec_slave[cnt].FMMU[j].PhysStart, ec_slave[cnt].FMMU[j].PhysStartBit,
                    ec_slave[cnt].FMMU[j].FMMUtype, ec_slave[cnt].FMMU[j].FMMUactive);
        }
        printf(" FMMUfunc 0:%d 1:%d 2:%d 3:%d\n", ec_slave[cnt].FMMU0func, ec_slave[cnt].FMMU1func,
                ec_slave[cnt].FMMU2func, ec_slave[cnt].FMMU3func);
    }
}

int ec_pdo_config(uint16 slave)
{
    int retval = 0;

    if (mode == 0)//csp mode
    {
        LOG_D("Set 0x1C12");
        retval += drive_write8(slave, 0x1C12, 0x00, 0);
        retval += drive_write16(slave, 0x1C12, 0x01, 0x1601);
        retval += drive_write8(slave, 0x1C12, 0x00, 1);
        LOG_D("Set 0x1C13");
        retval += drive_write8(slave, 0x1C13, 0x00, 0);
        retval += drive_write16(slave, 0x1C13, 0x01, 0x1A01);
        retval += drive_write8(slave, 0x1C13, 0x00, 1);

        retval += drive_write8(slave, 0x6060, 0x00, 0x08);
    }
    else if (mode == 1)//csv mode
    {
        LOG_D("Set 0x1C12");
        retval += drive_write8(slave, 0x1C12, 0x00, 0);
        retval += drive_write16(slave, 0x1C12, 0x01, 0x1602);
        retval += drive_write8(slave, 0x1C12, 0x00, 1);
        LOG_D("Set 0x1C13");
        retval += drive_write8(slave, 0x1C13, 0x00, 0);
        retval += drive_write16(slave, 0x1C13, 0x01, 0x1A02);
        retval += drive_write8(slave, 0x1C13, 0x00, 1);

        retval += drive_write8(slave, 0x6060, 0x00, 0x09);
    }

    if (retval != 7)
    {
        LOG_E("Config PDO failed!");
        return -1;
    }
    else
        LOG_D("Config PDO success.");

    return 0;
}

void ec_switch_op()
{
    do
    {
        if (mode == 0)
            cur_status = csp_inputs->StatusWord;
        else if (mode == 1)
            cur_status = csv_inputs->StatusWord;
        switch (cur_status & 0x006F)
        {
        case 0x0027:
            LOG_I("status: Operation enabled");
            if (mode == 0)
            {
                csp_outputs->ControlWord = 0x001F;
                csp_outputs->TargetPosition = 0;
            }
            else if (mode == 1)
                csv_outputs->TargetVelocity = 2;
            break;
        case 0x0000:
            LOG_I("status: Not ready to switch on");
            break;
        case 0x0040:
            LOG_I("status: Switched on but disabled");
            OUTPUT(ControlWord, 0x0006); //切换到ReadyToSwitchOn
            break;
        case 0x0021:
            LOG_I("status: Ready to switch on");
            OUTPUT(ControlWord, 0x0007); //切换到SwitchOn
            break;
        case 0x0023:
            LOG_I("status: Switched on");
            OUTPUT(ControlWord, 0x000F); //切换到OperationalEnable
            break;
        case 0x0008:
            LOG_I("status: Fault state");
            OUTPUT(ControlWord, 0x0080); //故障复位
            break;
        case 0x0007:
            LOG_I("status: Quickstop active");

            break;
        case 0x000F:
            LOG_I("status: Fault reaction active");

            break;
        default:
            LOG_E("Unhandled state: 0x%04X", cur_status & 0x006F);
            break;
        }
        ec_send_processdata();
        wkc = ec_receive_processdata(EC_TIMEOUTRET);

        rt_thread_mdelay(2);
    }while ((cur_status & 0x006F) != 0x0027);
}

void switch_to_dc()
{
    ecx_send_processdata(&ecx_context);
    wkc = ecx_receive_processdata(&ecx_context, EC_TIMEOUTRET);

    ecx_context.slavelist[slave].state = EC_STATE_SAFE_OP;
    ecx_writestate(&ecx_context, slave);
    ecx_statecheck(&ecx_context, slave, EC_STATE_SAFE_OP, 5000);
    if (ecx_context.slavelist[slave].state != EC_STATE_SAFE_OP)
    {
        LOG_E("Not all slaves reached Safe-Operational state.");
        ecx_readstate(&ecx_context);
        LOG_W("Slave %d State=0x%2x StatusCode=0x%04x : %s", 1, ecx_context.slavelist[1].state, ecx_context.slavelist[1].ALstatuscode,
                ec_ALstatuscode2string(ecx_context.slavelist[1].ALstatuscode));
    }

    ecx_context.slavelist[slave].state = EC_STATE_PRE_OP;
    ecx_writestate(&ecx_context, slave);
    ecx_statecheck(&ecx_context, slave, EC_STATE_PRE_OP, 5000);
    if (ecx_context.slavelist[slave].state != EC_STATE_PRE_OP)
    {
        LOG_E("Not all slaves reached Pre-Operational state.");
        ecx_readstate(&ecx_context);
        LOG_W("Slave %d State=0x%2x StatusCode=0x%04x : %s", 1, ecx_context.slavelist[1].state, ecx_context.slavelist[1].ALstatuscode,
                ec_ALstatuscode2string(ecx_context.slavelist[1].ALstatuscode));
    }

    memset(IOmap, 0, sizeof(IOmap));
    ec_pdo_config(1);
    ecx_configdc(&ecx_context);
    ecx_dcsync0(&ecx_context, 1, TRUE, 2500000, 50000);
    ecx_config_map_group(&ecx_context, &IOmap, currentgroup);

    ecx_context.slavelist[slave].state = EC_STATE_SAFE_OP;
    ecx_writestate(&ecx_context, slave);
    ecx_statecheck(&ecx_context, slave, EC_STATE_SAFE_OP, 5000);
    if (ecx_context.slavelist[slave].state != EC_STATE_SAFE_OP)
    {
        LOG_E("Not all slaves reached SAFE_OP state.");
        ecx_readstate(&ecx_context);
        LOG_W("Slave %d State=0x%2x StatusCode=0x%04x : %s", 1, ecx_context.slavelist[1].state, ecx_context.slavelist[1].ALstatuscode,
                ec_ALstatuscode2string(ecx_context.slavelist[1].ALstatuscode));
    }

    ecx_context.slavelist[slave].state = EC_STATE_OPERATIONAL;
    ecx_writestate(&ecx_context, slave);
    ecx_statecheck(&ecx_context, slave, EC_STATE_OPERATIONAL, 5000);
}

static volatile int delay = 0;
static void master_entry(void *ptr)
{
    const char *ifname = "e0";
    ecx_context.manualstatechange = 1;

    LOG_D("Starting initialise SOEM.");
    if (ecx_init(&ecx_context, ifname))
    {
        LOG_D("ec_init on %s succeeded.", ifname);

        wkc = ecx_config_init(&ecx_context, FALSE);
        if (wkc > 0)
        {
            ecx_context.slavelist[slave].state = EC_STATE_PRE_OP;
            ecx_writestate(&ecx_context, slave);
            ecx_statecheck(&ecx_context, slave, EC_STATE_PRE_OP, 5000);
            if (ecx_context.slavelist[slave].state != EC_STATE_PRE_OP)
            {
                LOG_E("Not all slaves reached Pre-Operational state.");
                ecx_readstate(&ecx_context);
                for(int i = 1; i <= *(ecx_context.slavecount) ; i++)
                {
                    if(ecx_context.slavelist[i].state != EC_STATE_PRE_OP)
                    {
                        LOG_W("Slave %d State=%2x StatusCode=%4x : %s\n",
                                i, ecx_context.slavelist[i].state, ecx_context.slavelist[i].ALstatuscode, ec_ALstatuscode2string(ecx_context.slavelist[i].ALstatuscode));
                    }
                }
            }

            ec_pdo_config(1);
            ecx_configdc(&ecx_context);
            ecx_config_map_group(&ecx_context, &IOmap, currentgroup);
            while (*(ecx_context.ecaterror)) LOG_E("%s", ecx_elist2string(&ecx_context));

            LOG_I("%d slaves found and configured.", *(ecx_context.slavecount));
            expectedWKC = (ec_group[0].outputsWKC * 2) + ec_group[0].inputsWKC;
            LOG_D("Calculated workcounter %d", expectedWKC);

            ecx_context.slavelist[slave].state = EC_STATE_SAFE_OP;
            ecx_writestate(&ecx_context, slave);
            ecx_statecheck(&ecx_context, slave, EC_STATE_SAFE_OP, 5000);
            if (ecx_context.slavelist[slave].state != EC_STATE_SAFE_OP)
            {
                LOG_E("Not all slaves reached Safe-Operational state.");
                ecx_readstate(&ecx_context);
                for(int i = 1; i <= *(ecx_context.slavecount) ; i++)
                {
                    if(ecx_context.slavelist[i].state != EC_STATE_SAFE_OP)
                    {
                        LOG_W("Slave %d State=%2x StatusCode=%4x : %s\n",
                                i, ecx_context.slavelist[i].state, ecx_context.slavelist[i].ALstatuscode, ec_ALstatuscode2string(ecx_context.slavelist[i].ALstatuscode));
                    }
                }
            }
            ecx_readstate(&ecx_context);
            show_slave_info();

            inOP = FALSE;

            LOG_D("Request Operational state for all slaves.");
            expectedWKC = (ec_group[0].outputsWKC * 2) + ec_group[0].inputsWKC;
            LOG_D("Calculated workcounter %d", expectedWKC);

            ecx_context.slavelist[slave].state = EC_STATE_OPERATIONAL;
            ecx_send_processdata(&ecx_context);
            wkc = ecx_receive_processdata(&ecx_context, EC_TIMEOUTRET);
            ecx_writestate(&ecx_context, slave);

            if (mode == 0)
            {
                csp_outputs = (CSP_Output *) ec_slave[slave].outputs;
                csp_inputs = (CSP_Input *) ec_slave[slave].inputs;
                csp_outputs->ControlWord = 0x0F;
            }
            else
            {
                csv_outputs = (CSV_Output *) ec_slave[slave].outputs;
                csv_inputs = (CSV_Input *) ec_slave[slave].inputs;
            }

            if (ecx_context.slavelist[slave].state == EC_STATE_OPERATIONAL)
            {
                LOG_I("Operational state reached for all slaves.");
                inOP = TRUE;

                ec_send_processdata();
                wkc = ec_receive_processdata(EC_TIMEOUTRET);

                ec_switch_op();
                switch_to_dc();

                while (inOP)
                {
                    ec_send_processdata();
                    wkc = ec_receive_processdata(EC_TIMEOUTRET);

                    if (delay == 100)
                        OUTPUT(ControlWord, 0x0000);
                    else if (delay == 150)
                        OUTPUT(ControlWord, 0x0080);
                    else if (delay == 200)
                        OUTPUT(ControlWord, 0x000F);
                    else if (delay == 250)
                    {
                        if (mode == 0)
                        {
                            csp_outputs->ControlWord = 0x001F;
                            csp_outputs->TargetPosition = 0;
                        }
                        else if (mode == 1)
                            csv_outputs->TargetVelocity = 2;
                    }
                    else if (delay > 250)
                    {
                        if (mode == 0)
                        {
                            update_textarea(ui_TextArea3, csp_inputs->ActualPosition);
                            if (delay % 100 == 0)
                                update_chart(chart1, ser1, csp_inputs->ActualPosition);
                        }
                        else
                        {
                            update_textarea(ui_TextArea2, csv_inputs->ActualVelocity);
                            if (delay % 100 == 0)
                                update_chart(chart2, ser2, csv_inputs->ActualVelocity);
                        }
                    }

                    delay++;
                    rt_thread_mdelay(2);
                }
                delay = 0;
            }
            else
            {
                LOG_E("Enter Operational failed!");
                ecx_close(&ecx_context);
            }
        }
        else
        {
            LOG_W("No slaves found.");
        }
    }
    else
    {
        LOG_E("ec_init failed!");
    }
}

void turn_off(void)
{
    if (thread1 != RT_NULL)
    {
        LOG_I("Turn off.");
        OUTPUT(ControlWord, 0x0000);
        ec_send_processdata();
        ec_receive_processdata(EC_TIMEOUTRET);
        inOP = FALSE;
        ecx_close(&ecx_context);
    }
}

void turn_on(void)
{
    active_master();
}

void set_data(int32_t data)
{
    if (mode == 0)
        csp_outputs->TargetPosition = data;
    else
        csv_outputs->TargetVelocity = data;
}

static void textarea_update_cb(void * user_data)
{
    textarea_update_t * data = (textarea_update_t *)user_data;

    if (data && data->ta)
        lv_textarea_set_text(data->ta, data->text);

    rt_free(data);
}

void update_textarea(lv_obj_t * ta, int32_t value)
{
    textarea_update_t * data = rt_malloc(sizeof(textarea_update_t));
    if (data == NULL) return;

    data->ta = ta;
    rt_snprintf(data->text, sizeof(data->text), "%"LV_PRId32, value);

    lv_async_call(textarea_update_cb, data);
}

static void chart_update_cb(void * user_data)
{
    chart_update_t * data = (chart_update_t *)user_data;

    if (data && data->chart && data->series)
        lv_chart_set_next_value(data->chart, data->series, data->value);

    rt_free(data);
}

void update_chart(lv_obj_t * chart, lv_chart_series_t * series, int16_t value)
{
    chart_update_t * data = rt_malloc(sizeof(chart_update_t));
    if (data == NULL) return;

    data->chart = chart;
    data->series = series;
    data->value = value;

    lv_async_call(chart_update_cb, data);
}

int master(int argc, char **argv)
{
    if (argc > 1)
    {
        if (!strcmp(argv[1], "setC"))
        {
            OUTPUT(ControlWord, atoi(argv[2]));
            ec_send_processdata();
            ec_receive_processdata(EC_TIMEOUTRET);
            printf("\nSet Control Word 0x%04x\n", atoi(argv[2]));
        }
        else if (!strcmp(argv[1], "getError"))
        {
            ec_send_processdata();
            ec_receive_processdata(EC_TIMEOUTRET);
            printf("\nGet Error Code 0x%04x\n", INPUT(ErrorCode));
        }
        else if (!strcmp(argv[1], "getStatus"))
        {
            ec_send_processdata();
            ec_receive_processdata(EC_TIMEOUTRET);
            printf("\nGet Status Code 0x%04x\n", INPUT(StatusWord & 0x006F));
        }
        else if (!strcmp(argv[1], "setP"))
        {
            csp_outputs->TargetPosition = atoi(argv[2]);
            ec_send_processdata();
            ec_receive_processdata(EC_TIMEOUTRET);
            printf("\nSet Target Position %d\n", atoi(argv[2]));
        }
        else if (!strcmp(argv[1], "getP"))
        {
            ec_send_processdata();
            ec_receive_processdata(EC_TIMEOUTRET);
            printf("\nGet Actual Position %"LV_PRId32"\n", csp_inputs->ActualPosition);
        }
        else if (!strcmp(argv[1], "setV"))
        {
            csv_outputs->TargetVelocity = atoi(argv[2]);
            ec_send_processdata();
            ec_receive_processdata(EC_TIMEOUTRET);
            printf("\nSet Target Velocity %d\n", atoi(argv[2]));
        }
        else if (!strcmp(argv[1], "getV"))
        {
            ec_send_processdata();
            ec_receive_processdata(EC_TIMEOUTRET);
            printf("\nGet Actual Velocity %"LV_PRId32"\n", csv_inputs->ActualVelocity);
        }
        else if (!strcmp(argv[1], "getState"))
        {
            uint8 slave = atoi(argv[2]);
            ecx_send_processdata(&ecx_context);
            ecx_receive_processdata(&ecx_context, EC_TIMEOUTRET);
            ecx_readstate(&ecx_context);
            printf("\nGet slave %d state 0x%04x\n", slave, ecx_context.slavelist[slave].state);
        }
        else if (!strcmp(argv[1], "toSOP"))
        {
            ecx_context.slavelist[1].state = EC_STATE_SAFE_OP + EC_STATE_ACK;
            ecx_writestate(&ecx_context, 1);
            printf("\nRequest Safe-Operational for salve 1\n");
        }
        else if (!strcmp(argv[1], "setMode"))
        {
            mode = atoi(argv[2]);
            printf("\nSet motor mode to %d\n", mode);
            turn_off();
            rt_thread_mdelay(500);
            turn_on();
        }
        else if (!strcmp(argv[1], "getMode"))
        {
            printf("\nGet motor mode %d\n", mode);
        }
        else if (!strcmp(argv[1], "close"))
        {
            ecx_close(&ecx_context);
            printf("\nMaster close\n");
        }
    }
    else
    {
        rt_kprintf("Usage: \n");
        rt_kprintf("master getError           - get Error Code\n");
        rt_kprintf("master getStatus          - get Status Code\n");
        rt_kprintf("master getState <slave>   - get State Code of slave\n");
        rt_kprintf("master getP               - get Actual Position\n");
        rt_kprintf("master setP <position>    - set Target Position\n");
        rt_kprintf("master getV               - get Actual Velocity\n");
        rt_kprintf("master setV <velocity>    - set Target Velocity\n");
        rt_kprintf("master setC <ControlWord> - set Control Word\n");
        rt_kprintf("master toSOP              - request Safe-Operationl\n");
        rt_kprintf("master setMode <mode>     - set motor mode(0:csp, 0:csv)\n");
    }

    return 0;
}
MSH_CMD_EXPORT(master, set/get pdo data);

int active_master()
{
    thread1 = rt_thread_create("master", master_entry, RT_NULL, 4096, 15, 10);
    rt_thread_startup(thread1);
    return 0;
}
MSH_CMD_EXPORT(active_master, active master);
