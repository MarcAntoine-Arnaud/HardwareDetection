env = Environment(CPPPATH = ['include'])

env.Library('MyHardware', ['src/MyHardware.cpp'])

env.Program('app/cpu.cpp', LIBS=['MyHardware'], LIBPATH='.')
