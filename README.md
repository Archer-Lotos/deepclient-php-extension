# Deep Client Php Extension


Deep Client - a way to connect your favourite language with Deep.

## Install/Build
```bash
pip install -r requirements.txt
python setup.py build_ext --inplace
```

#### Or
```bash
phpize
./configure --enable-deep_client_php_extension
make
```

#### Or
```bash
apt-get install autoconf cmake make automake libtool git libboost-all-dev libssl-dev g++
cmake .
make

/etc/init.d/php8.1-fpm restart
```

## Running Tests Python

```bash
python -m unittest discover -s tests -v
python -m unittest tests.test_select.TestDeepClientSelect.testSelect
```