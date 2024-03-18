venv:
  python3 -m venv .venv
  source .venv/bin/activate
  pip install cmake pyside6

build:
  cmake -S . -B build/
  cmake --build build/

run:
  ./bin/Deepcore
