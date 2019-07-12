ACTIVATE='venv/bin/activate'

if [ -z "${VIRTUAL_ENV}" ]; then
  if [ ! -f "${ACTIVATE}" ]; then
    python -m venv venv
  fi
  . $ACTIVATE
fi

pip install -U pip setuptools yamllint esphome
pio platform update
