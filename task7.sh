   #!/usr/local/bin/env bash
   # task7.sh — вбудовуємо логування в bash через DEBUG-trap

   # Куди писати лог
   LOGFILE="$HOME/.user_commands.log"
   
   # Створимо/очистимо файл і дамо права тільки нам
   : > "$LOGFILE"
   chmod 600 "$LOGFILE"

   # Кожну команду перед виконанням пишемо в лог (фіксується час, user, pwd і сама команда):
   trap 'printf "%s %s %s %s\n" \
     "$(date "+%Y-%m-%d %H:%M:%S")" "$USER" "$PWD" "$BASH_COMMAND" \
     >> "$LOGFILE"' DEBUG
