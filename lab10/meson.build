# NOTE: This may only work on Windows.
# https://stackoverflow.com/q/23397536

project('lab10', 'cpp',
  default_options: ['cpp_std=c++17'])

add_project_arguments('-DSFML_STATIC', language: 'cpp')

sfml_dir = get_option('sfml_dir')
sfml_inc = include_directories(sfml_dir / 'include')
sfml_libdir = sfml_dir / 'lib'
sfml = declare_dependency(
  include_directories: sfml_inc,
  link_args: [
    '-L' + sfml_libdir,
    '-lsfml-graphics-s',
    '-lsfml-window-s',
    '-lsfml-system-s',
    '-lopengl32',
    '-lwinmm',
    '-lfreetype',
    '-lgdi32'])

memer = static_library('memer', 'memer.cpp', dependencies: sfml)
executable('memeify', 'memeify.cpp', link_with: memer, dependencies: sfml)
