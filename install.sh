ACTIVATE='venv/bin/activate'

if [ -z "${VIRTUAL_ENV}" ]; then
  if [ ! -f "${ACTIVATE}" ]; then
    python -m venv venv
  fi
  . $ACTIVATE
fi

pip install -U pip setuptools https://github.com/platformio/platformio-core/archive/develop.zip yamllint esphome
pio platform update
