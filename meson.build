project('star renderer', 'c')
compiler = meson.get_compiler('c', native: true)

#host_system = host_machine.system()

sources = [
    './src/main.c',
    './src/engine/glad.c',
    './src/engine/gl/gl.c',
    './src/engine/gl/callbacks.c',
    './src/engine/gl/renderer.c',
    './src/engine/io/file.c',
]

include_dir = include_directories('include')

glfw = compiler.find_library('glfw3', dirs:'E:\\programas\\C\\StarRenderer\\lib', required:true, static:true)

executable('star', sources, include_directories: include_dir, dependencies: glfw, install: true, install_dir:'E:\\programas\\C\\StarRenderer\\bin')