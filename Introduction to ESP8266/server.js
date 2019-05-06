/*
*   Test server for ESP8266WiFi and ESP8266HTTPClient libraries
*   http://www.projetsdiy.fr - 2017
*/
var express = require('express');
var moment = require('moment');
var app = express();

app.get('/', function(req, res) {
  res.send('HTTP ESP8266 Test Server')
});

app.use('/watchdog', function (req, res, next) {
  var t = moment.duration(parseInt(req.param('uptime')), 'milliseconds')
  var _message = req.param('ip') + " uptime " + t.hours() + "h " + t.minutes() + "m " + t.seconds() +"s";
  console.log("watchdog from " + _message);
  res.send("You are alive!");
});

app.listen(8080);
