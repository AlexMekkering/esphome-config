ACTIVATE='venv/bin/activate'

if [ -z "${VIRTUAL_ENV}" ]; then
  if [ ! -f "${ACTIVATE}" ]; then
    python -m venv venv
  fi
  . $ACTIVATE
fi
pip install -U pip setuptools pipenv

export PIPENV_VERBOSITY=-1
pipenv install

pio platform update
