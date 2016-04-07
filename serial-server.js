var io = require('socket.io')(8082);
var fs = require('fs');
var sp = require("serialport");


var serialPort = new sp.SerialPort("/dev/cu.usbmodem1421", {
  baudrate: 9600,
  parser: sp.parsers.readline("\n")
});



 // serialPort.on("open", function () {

 //    console.log('opened');

 //    serialPort.on('data', function(val) {
 //      console.log('data received: ' + val);
 //     // socket.emit('moveDial', val);
 //    });

 //  });


var theSock;

io.on('connection', function (socket) {
  console.log('connected');
  theSock = socket;


  // socket.emit('news', { hello: 'world' });
  // socket.on('my other event', function (data) {
  //   console.log(data);
  // });

  theSock.on("uiDialChange", function (val) {

    console.log(val);
    
    
    serialPort.write(val.toString());
    serialPort.write("\n");

  });

});

serialPort.on("open", function () {

  console.log('opened');

});



serialPort.on('data', function(val) {
  console.log('data received: ' + val);
  theSock && theSock.emit('moveDial', val);
});

