 /** \file
  * \brief Example code for Simple Open EtherCAT master
  *
  * Usage : simple_test [ifname1]
  * ifname is NIC interface, f.e. eth0
  *
  * This is a minimal test.
  *
  * (c)Arthur Ketels 2010 - 2011
  */
#if 0
 #include <stdio.h>
 #include <string.h>
 #include <inttypes.h>

 #include "ethercat.h"
#ifdef BSP_USING_MOCOT
#include "motorctrl.h"
#elif defined(BSP_USING_MOCOT_MY)
 #include "myservo.h"
#endif

 #define EC_TIMEOUTMON 500

 //char IOmap[4096];
 OSAL_THREAD_HANDLE thread1;
 OSAL_THREAD_HANDLE thread2;
 int expectedWKC;
 boolean needlf;
 volatile int wkc;
 boolean inOP;
 uint8 currentgroup = 0;
 char *myifname;
 unsigned int testtimes = 0;

 //void simpletest(char *ifname)
 //{
 //   printf("Starting simple test\n");
 //}

 static OSAL_THREAD_FUNC ecatcheck( void *ptr )
 {
     int slave;
     (void)ptr;                  /* Not used */

     while(1)
     {
         if( inOP && ((wkc < expectedWKC) || ec_group[currentgroup].docheckstate))
         {
             if (needlf)
             {
                needlf = FALSE;
                printf("\n");
             }
             /* one ore more slaves are not responding */
             ec_group[currentgroup].docheckstate = FALSE;
             ec_readstate();
             for (slave = 1; slave <= ec_slavecount; slave++)
             {
                if ((ec_slave[slave].group == currentgroup) && (ec_slave[slave].state != EC_STATE_OPERATIONAL))
                {
                   ec_group[currentgroup].docheckstate = TRUE;
                   if (ec_slave[slave].state == (EC_STATE_SAFE_OP + EC_STATE_ERROR))
                   {
                      printf("ERROR : slave %d is in SAFE_OP + ERROR, attempting ack.\n", slave);
                      ec_slave[slave].state = (EC_STATE_SAFE_OP + EC_STATE_ACK);
                      ec_writestate(slave);
                   }
                   else if(ec_slave[slave].state == EC_STATE_SAFE_OP)
                   {
                      printf("WARNING : slave %d is in SAFE_OP, change to OPERATIONAL.\n", slave);
                      ec_slave[slave].state = EC_STATE_OPERATIONAL;
                      ec_writestate(slave);
                   }
                   else if(ec_slave[slave].state > EC_STATE_NONE)
                   {
                      if (ec_reconfig_slave(slave, EC_TIMEOUTMON))
                      {
                         ec_slave[slave].islost = FALSE;
                         printf("MESSAGE : slave %d reconfigured\n",slave);
                      }
                   }
                   else if(!ec_slave[slave].islost)
                   {
                      /* re-check state */
                      ec_statecheck(slave, EC_STATE_OPERATIONAL, EC_TIMEOUTRET);
                      if (ec_slave[slave].state == EC_STATE_NONE)
                      {
                         ec_slave[slave].islost = TRUE;
                         printf("ERROR : slave %d lost\n",slave);
                      }
                   }
                }
                if (ec_slave[slave].islost)
                {
                   if(ec_slave[slave].state == EC_STATE_NONE)
                   {
                      if (ec_recover_slave(slave, EC_TIMEOUTMON))
                      {
                         ec_slave[slave].islost = FALSE;
                         printf("MESSAGE : slave %d recovered\n",slave);
                      }
                   }
                   else
                   {
                      ec_slave[slave].islost = FALSE;
                      printf("MESSAGE : slave %d found\n",slave);
                   }
                }
             }
             if(!ec_group[currentgroup].docheckstate)
                printf("OK : all slaves resumed OPERATIONAL.\n");
         }
//         osal_usleep(10000);
         rt_thread_mdelay(10);
     }
 }

 OSAL_THREAD_FUNC myecattask( void *ptr )
 {
    (void)ptr;                  /* Not used */
//    ethercat_thread_entry();
//    motorctrl_init();
//    SVX3E_config(myifname);
    simpletest("e0");
 }

 int simple_main(int argc, char *argv[])
 {
    printf("SOEM (Simple Open EtherCAT Master)\nSimple test\n");
    testtimes = 20000;
    /* create thread to handle slave error handling in OP */
    //pthread_create( &thread1, NULL, (void *) &ecatcheck, (void*) &ctime);
    //osal_thread_create(&thread1, 128000, &ecatcheck, (void*) &ctime);
    osal_thread_create(&thread1, 12800, &ecatcheck, NULL);
    /* start cyclic part */
    //simpletest(argv[1]);
    myifname = "e0";
    osal_thread_create(&thread2, 12800, &myecattask, NULL);
    while(1)
    {
//       osal_usleep(1000);//1ms,只控制总运行时间,与ECAT周期无关
          rt_thread_mdelay(1);
 //      testtimes--;
    }
 //   servo_switch_idle();

    printf("End program\n");
    return (0);
 }
 MSH_CMD_EXPORT(simple_main, simple_main);

 void simple_app(void)
 {
     rt_thread_t res = rt_thread_create("simple_app", simple_main, RT_NULL, 10240, 15, 10);
     rt_thread_startup(res);
 }
 MSH_CMD_EXPORT(simple_app, simple_app);
#endif
