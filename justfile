venv:
  python3 -m venv .venv
  source .venv/bin/activate
  pip install cmake pyside6

build:
  cmake -S . -B build/ -G Ninja
  cmake --build build/

install:
  cmake --install build/ --prefix .

run:
  ./bin/Deepcore
