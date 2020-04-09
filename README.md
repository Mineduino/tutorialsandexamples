# Private node-red and mqtt-broker deployment

You can easily deploy the package of node-red and mqtt-broker to the heroku for free!
Free accounts have here 1000 hours per month, so you can run this forever.

It will turns off the machine due to inactivity, so sometimes you have just go to the dashboard.

Batteries included - dashboard and broker is secured by https and passwords.
Default:
L: admin
H: admin

Change passwords by executing nodes, check out **self-hosted-heroku/flows.json** and import it into your nodered!
Then you can just change the exec node, and that's it!

After deploying you will have to wait ~ 1 minute.

[![Deploy](https://www.herokucdn.com/deploy/button.svg)](https://heroku.com/deploy?template=https://github.com/Mineduino/tutorialsandexamples/tree/master)
