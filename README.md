# Deep Client Php Extension


Deep Client - a way to connect your favourite language with Deep.

## Install/Build

```
pip install -r requirements.txt
python setup.py build_ext --inplace
```

## Running Tests Python

```
python -m unittest discover -s tests -v
python -m unittest tests.test_select.TestDeepClientSelect.testSelect
```