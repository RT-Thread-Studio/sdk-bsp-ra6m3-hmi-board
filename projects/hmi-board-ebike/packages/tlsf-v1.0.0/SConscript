import os
from building import *

src = []
group = []

cwd = GetCurrentDir()
src = Split("""
rt_tlsf.c
src/tlsf.c
""")
CPPPATH = [cwd + '/src']

group = DefineGroup('tlsf', src, depend = ['PKG_USING_TLSF', 'RT_USING_USERHEAP'], CPPPATH = CPPPATH)

Return('group')
