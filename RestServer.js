var bodyParser = require('body-parser')
const express = require('express');
const app = express();

app.use(bodyParser.urlencoded({extended: true})) 
app.use(bodyParser.json()) 

var status = [
    {id: 'DeviceName'},
    {spawn: false},
    {feeding: false},
    {hello: false},
    {hide: false},
    {belly: false},
    {getclose: false},
    {endclose: false},
    {spin: false},
    {reset: false},
    {startdance: false},
    {enddance: false}
]

app.get('/status', function(req,res) {
    //Select User logic ......
    res.send(status);
});

app.post('/status', function(req,res) {
    status = (
        {
            id: req.body.id, 
            spawn: req.body.spawn,
            feeding: req.body.feeding,
            hello: req.body.hello,
            hide: req.body.hide,
            belly: req.body.belly,
            getclose: req.body.getclose,
            endclose: req.body.endclose,
            spin: req.body.spin,
            reset: req.body.reset
        }
    )
    res.send(status)
});

app.get('/dance', function(req,res) {
    //Select User logic ......
    res.send(status);
});

app.post('/dance', function(req,res) {
    status = (
        {
            id: req.body.id, 
            startdance: req.body.startdance,
            enddance: req.body.enddance
        }
    )
    console.log(status)
    res.send(status)
});

// app.delete('/user', function(req,res) {
//     //Delete User logic ......
//     res.send(user); 
// });

app.listen(8080, function (){
    console.log('Server is Running')
    
});

