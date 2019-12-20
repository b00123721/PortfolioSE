var http = require('http');

var fs = require('fs');



function handle_incoming_request (req, res) {

    console.log("INCOMING REQUEST: " + req.method + " " + req.url);

    load_sensor_data(function(err, readings){

    if (err) { 

       console.log("Couldn't read file");

    }


    var splitteddata = readings.split(',');


    
    console.log(readings);

    console.log(splitteddata[1]);



    res.writeHead(200, { "Content-Type" : "application/json" });

    res.end(JSON.stringify({temperature : splitteddata[0], humidity : splitteddata[1], windspeed : splitteddata[2], time : splitteddata[3], location : splitteddata[4]}));

   });

}



function load_sensor_data(callback) {

   fs.readFile(

   "sensorlog.txt",'utf8',

   function (err, readings) {

   if (err) {
 
   callback(err);

return;



}

callback(null, readings);

}

);

}

var s = http.createServer(handle_incoming_request);


s.listen(8080)