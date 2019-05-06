/**
 * A socket.io server that serves a static website and
 * sends events from the ESP8266 to the website
 */

// Import libraries
var express = require('express');
var app = express();

// Send test data back to the client
app.get('/', function(req, res) {
  res.send('Hello, world!');
});

// Start the server on port 3000
app.listen(3000);