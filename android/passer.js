var net = require("net");
var WebSocketServer = require('ws').Server;

var linux = net.connect({
    port: 8124
}, function() { //'connection' listener
    console.log('linux connected');

    // c.on('end', function() {
    //     console.log('linux disconnected');
    // });
});

// server.listen(8124, function() { //'listening' listener
//     console.log('server bound');
// });

var wss = new WebSocketServer({port: 9002});
wss.on("connection", function(client) {
    client.on("message", function (data) {
        console.log("passing", data);
        linux.write(data);
    });
});
