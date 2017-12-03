# ping-pong
> Ping-Arkanoid-Pong game by Pongcats team :cat:

Мы - команда *Pongcats*, и мы занимаемся созданием одной из самых замечательных игр: прямиком из прошлого в светлое будущее - arkanoid. Но, так как изначально мы не решили, что же это будет - arkanoid или pong, мы решили сделать всё и сразу - начав разработку с pong'a, мы постепенно пришли к идеи полноценного арканоида.

## Скриншоты игрового процесса
![alt tag](https://pp.userapi.com/c841326/v841326566/31fcb/muViS6lubTU.jpg)
![alt tag](https://pp.userapi.com/c824204/v824204772/193b0/0579jD13-wM.jpg)

## Цель
Получить полноценный арканоид с примесью pong'а для мальчишек и девчонок, а также их родителей

## Разработчики
- Манашев Ильдар
- Недяк Маша
- Николаев Антон

## Используемые инструменты разработки
- Cocos2d-x
- CLion
- CMake
- Google-tests
- Bash/shell скрипты собственного производства

## Текущий функционал
- Полноценный играбельный арканоид
- Звуковые эффекты
- Графика и графическое оформление

## В прогрессе
- Система бонусов
- Игровое поле (кирпичи и другие объекты)
- Игровая физика
- Генерация уровней

# Сборка проекта
Наш проект собирается легко, как дважды два, и вкусно, как домашние печеньки
## Linux:
_Совет:_ чтобы избежать возможных проблем с совместимостью и т.д., отключите `fish`, `zsh` или любой ваш текущий кастомный шелл, и на время сборки воспользуйтесь стандартным `bash` вашей системы. Перед тем, как запустить сборку проекта, убедитесь, что cocos2d-x установлен в вашей системе, в ином случае воспользуйтесь shell-скриптом из нашего репозитория: 
https://github.com/tsu-trpo/ping-pong/tree/master/Cocos-install-script

Обратите внимание на то, что первая команда опциональна - в зависимости от того, используете Вы https или ssh.
###### On bash:
```
git clone git@github.com:tsu-trpo/ping-pong.git or git clone https://github.com/tsu-trpo/ping-pong.git
cd ping-pong/SUPER-PING-PONG/
git submodule update --recursive --init
cocos run -p linux
```
В случае, если запуск через команду `cocos` не удался или что-то пошло не так, Вы можете воспользоваться альтернативным вариантом сборки проекта:  
###### On bash:
```
git clone git@github.com:tsu-trpo/ping-pong.git or git clone https://github.com/tsu-trpo/ping-pong.git
cd ping-pong/SUPER-PING-PONG/
git submodule update --recursive --init
mkdir build && cd build
cmake ..
make
cd bin/
./pong
```
