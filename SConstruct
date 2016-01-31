AddOption('--build-release',
          dest='build-release',
          action="store_true",
          help='build in release mode (exclusive with debug mode)')

AddOption('--build-debug',
          dest='build-debug',
          action="store_true",
          help='build in debug mode (exclusive with release mode)')

is_debug = False
is_release = False
build_dir = 'build/release/'

if GetOption('build-debug'):
    build_dir = 'build/debug/'
    is_debug = True

if GetOption('build-release'):
    build_dir = 'build/release/'
    is_release = True

if is_release and is_debug:
    print "Build script does not support both release and debug"
    System.exit(-1)

Sources = ['src/queenbee.c',
           'src/unix_toolkit.c']

env = Environment(CPPPATH = ['./include/'])
if is_release:
    env.Append(CCFLAGS = '-O2')
elif is_debug:
    env.Append(CCFLAGS = '-g -Wall')
env.Program(build_dir+ 'bin/queenbee', Sources)
