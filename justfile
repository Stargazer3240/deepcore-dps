venv:
  python3 -m venv .venv
  source .venv/bin/activate
  pip install cmake pyside6

build:
  cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=1 -S . -B build/
  cmake --build build/
