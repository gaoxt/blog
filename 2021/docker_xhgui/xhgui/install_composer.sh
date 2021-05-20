#!/bin/sh
php -r "copy('https://install.phpcomposer.com/installer', 'composer-setup.php');"
php composer-setup.php
php -r "unlink('composer-setup.php');"
mv composer.phar /usr/local/bin/composer
composer config -g repo.packagist composer https://packagist.phpcomposer.com
composer config --global --auth github-oauth.github.com token
sed -i 's/token/16062c7d17fd832bb0fa5de2b41db48fbd0aa793/g' /root/.composer/auth.json