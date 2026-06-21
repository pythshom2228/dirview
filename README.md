# DirView

DirView — графическое приложение на Qt5 для просмотра файловой системы Linux.

Проект основан на примере `itemviews/dirview` из Qt и расширен дополнительными возможностями.

## Возможности

* отображение файлов и каталогов в виде дерева;
* стартовая директория — домашний каталог пользователя, запустившего программу;
* отображение скрытых файлов и каталогов;
* сортировка содержимого по столбцам;
* фильтрация файлов и каталогов по имени через поле поиска;
* вычисление размера каталогов по запросу пользователя;
* сборка Debian-пакета;
* автоматическая сборка пакета через GitHub Actions.

## Требования

* Linux
* CMake 3.16+
* Qt 5
* C++17

Для Debian/Astra Linux:

```bash
sudo apt install qtbase5-dev cmake build-essential
```

## Сборка
```bash
git clone https://github.com/pythshom2228/dirview.git
cd dirview
```

### CMake
```bash
mkdir build
cd build

cmake ..
cmake --build .
```

### QMake
```bash
mkdir build
cd build

qmake ..
make
```

Запуск:

```bash
./dirview
```
## Debian-пакет

Для сборки пакета необходимо установить инструменты пакетирования:

```bash
sudo apt install debhelper devscripts
```

Сборка пакета:

```bash
dpkg-buildpackage -us -uc
```
Все изменения относительно оригинального примера в debian/patches/dirview-features.patch

## CI/CD

В проекте настроен GitHub Actions.

При публикации нового Release автоматически:

1. выполняется сборка проекта;
2. создаётся Debian-пакет;
3. пакет прикрепляется к опубликованному релизу GitHub.
