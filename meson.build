project('star renderer', 'c', default_options: ['c_std=c11'])
compiler = meson.get_compiler('c', native: true)

#host_system = host_machine.system()

add_global_arguments(['-static-libgcc', '-ggdb', '-Wlarger-than=1000' ], language:'c')

sources = [
    './src/main.c',
    './src/engine/glad.c',
    './src/engine/gl/gl.c',
    './src/engine/gl/callbacks.c',
    './src/engine/gl/renderer.c',
    './src/engine/io/file.c',
    './src/engine/io/simplemd2.c',
]

include_dir = include_directories('include')
cglm_include_dir = include_directories('E:\\DevTools\\cglm\\include')

#assimp_include = include_directories('E:\\DevTools\\assimp-5.2.5\\include')
#assimp_include_config = include_directories('E:\\DevTools\\assimpbuild\\include')

glfw = compiler.find_library('glfw3', dirs:'E:\\programas\\C\\StarRenderer\\lib', required:true, static:true)
cglm = compiler.find_library('cglm', dirs: 'E:\\DevTools\\cglm\\build', required: true)
#assimp = compiler.find_library('assimp.dll', dirs:'E:\\DevTools\\assimpbuild\\lib', required:true)
executable('star', sources, include_directories: [include_dir, cglm_include_dir], dependencies: [glfw, cglm], install: true, install_dir:'E:\\programas\\C\\StarRenderer\\bin')