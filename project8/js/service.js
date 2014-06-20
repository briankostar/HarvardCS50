/**
 * service.js
 *
 * Computer Science 50
 * Problem Set 8
 *
 * Implements a shuttle service.
 */

// default height
var HEIGHT = 0.8;

// default latitude
var LATITUDE = 42.3745615030193;

// default longitude
var LONGITUDE = -71.11803936751632;

// default heading
var HEADING = 1.757197490907891;

// default number of seats
var SEATS = 10;

// default velocity
var VELOCITY = 50;

// global reference to shuttle's marker on 2D map
var bus = null;

// global reference to 3D Earth
var earth = null;

// global reference to 2D map
var map = null;

// global reference to shuttle
var shuttle = null;

// load version 1 of the Google Earth API
google.load("earth", "1");

// load version 3 of the Google Maps API
google.load("maps", "3", {other_params: "sensor=false"});

// once the window has loaded
$(window).load(function() {

    // listen for keydown anywhere in body
    $(document.body).keydown(function(event) {
        return keystroke(event, true);
    });

    // listen for keyup anywhere in body
    $(document.body).keyup(function(event) {
        return keystroke(event, false);
    });

    // listen for click on Drop Off button
    $("#dropoff").click(function(event) {
        dropoff();
    });

    // listen for click on Pick Up button
    $("#pickup").click(function(event) {
        pickup();
    });
    
    $("#timer").click(function(event) {
        timer();
    });

    $("#set_speed").click(function(event) {
        setspeed();
    });
    
    $("#set_size").click(function(event) {
        setsize();
    });
    
    // load application
    load();
});

// unload application
$(window).unload(function() {
    unload();
});

/**
 * Renders seating chart.
 */
var seats_available = SEATS;
function chart()
{
    var html = "<ol start='0'>";
    for (var i = 0; i < shuttle.seats.length; i++)
    {
        if (shuttle.seats[i] == null)
        {
            html += "<li style='color: red'>Empty Seat</li>";
        }
        else
        {
            var house;
            for (var j in PASSENGERS){
                if(shuttle.seats[i] == PASSENGERS[j]["name"]){
                house = PASSENGERS[j]["house"];
                }
            }
            html += "<li style='color: blue'>" + shuttle.seats[i] + " to " + house + "</li>";
        }
    }
    html += "</ol>";
    $("#chart").html(html);
}

/**
 * Drops up passengers if their stop is nearby.
 */
function dropoff()
{
    //check distance to each passenger's house.
    //if distance < 30 drop off
    //data i have is.. name of students
    var dropcount = 0;
    for(var i in shuttle.seats){
        if(shuttle.seats[i] != null){
            for(var j in PASSENGERS){
                //if this passenger's name is same as PASSENGER's name, get that lat/lng
                if(shuttle.seats[i] == PASSENGERS[j]["name"]){
                    var lat = PASSENGERS[j]["final_lat"];
                    var lng = PASSENGERS[j]["final_lng"];
                    //check distance
                    var d = shuttle.distance(lat, lng);
                    if(d < 30){
                        shuttle.seats[i] = null;
                        seats_available += 1; 
                        dropcount += 1;
                        chart();
                    }
                }
            }
        }
    }
    if (dropcount == 0){
        $("#announcements").html("Can't drop off here!");
    }
    else if(dropcount == 1){
        $("#announcements").html("One student dropped off.");
    }else{
        $("#announcements").html("Students dropped off.");
    }
    
    
}

/**
 * Called if Google Earth fails to load.
 */
function failureCB(errorCode) 
{
    // report error unless plugin simply isn't installed
    if (errorCode != ERR_CREATE_PLUGIN)
    {
        alert(errorCode);
    }
}

/**
 * Handler for Earth's frameend event.
 */
function frameend() 
{
    shuttle.update();
}

/**
 * Called once Google Earth has loaded.
 */
function initCB(instance) 
{
    // retain reference to GEPlugin instance
    earth = instance;

    // specify the speed at which the camera moves
    earth.getOptions().setFlyToSpeed(100);

    // show buildings
    earth.getLayerRoot().enableLayerById(earth.LAYER_BUILDINGS, true);

    // disable terrain (so that Earth is flat)
    earth.getLayerRoot().enableLayerById(earth.LAYER_TERRAIN, false);

    // prevent mouse navigation in the plugin
    earth.getOptions().setMouseNavigationEnabled(false);

    // instantiate shuttle
    shuttle = new Shuttle({
        heading: HEADING,
        height: HEIGHT,
        latitude: LATITUDE,
        longitude: LONGITUDE,
        planet: earth,
        seats: SEATS,
        velocity: VELOCITY
    });

    // synchronize camera with Earth
    google.earth.addEventListener(earth, "frameend", frameend);

    // synchronize map with Earth
    google.earth.addEventListener(earth.getView(), "viewchange", viewchange);

    // update shuttle's camera
    shuttle.updateCamera();

    // show Earth
    earth.getWindow().setVisibility(true);

    // render seating chart
    chart();

    // populate Earth with passengers and houses
    populate();
    
}

/**
 * Handles keystrokes.
 */
function keystroke(event, state)
{
    // ensure we have event
    if (!event)
    {
        event = window.event;
    }

    // left arrow
    if (event.keyCode == 37)
    {
        shuttle.states.turningLeftward = state;
        $("#announcements").html(" ");
        return false;
    }

    // up arrow
    else if (event.keyCode == 38)
    {
        shuttle.states.tiltingUpward = state;
        $("#announcements").html(" ");
        return false;
    }

    // right arrow
    else if (event.keyCode == 39)
    {
        shuttle.states.turningRightward = state;
        $("#announcements").html(" ");
        return false;
    }

    // down arrow
    else if (event.keyCode == 40)
    {
        shuttle.states.tiltingDownward = state;
        $("#announcements").html(" ");
        return false;
    }

    // A, a
    else if (event.keyCode == 65 || event.keyCode == 97)
    {
        shuttle.states.slidingLeftward = state;
        $("#announcements").html(" ");
        return false;
    }

    // D, d
    else if (event.keyCode == 68 || event.keyCode == 100)
    {
        shuttle.states.slidingRightward = state;
        $("#announcements").html(" ");
        return false;
    }
  
    // S, s
    else if (event.keyCode == 83 || event.keyCode == 115)
    {
        shuttle.states.movingBackward = state;     
        $("#announcements").html(" ");
        return false;
    }

    // W, w
    else if (event.keyCode == 87 || event.keyCode == 119)
    {
        shuttle.states.movingForward = state;   
        $("#announcements").html(" "); 
        return false;
    }
  
    return true;
}

/**
 * Loads application.
 */
function load()
{
    // embed 2D map in DOM
    var latlng = new google.maps.LatLng(LATITUDE, LONGITUDE);
    map = new google.maps.Map($("#map").get(0), {
        center: latlng,
        disableDefaultUI: true,
        mapTypeId: google.maps.MapTypeId.ROADMAP,
        scrollwheel: false,
        zoom: 17,
        zoomControl: true
    });

    // prepare shuttle's icon for map
    bus = new google.maps.Marker({
        icon: "https://maps.gstatic.com/intl/en_us/mapfiles/ms/micons/bus.png",
        map: map,
        title: "you are here"
    });

    // embed 3D Earth in DOM
    google.earth.createInstance("earth", initCB, failureCB);
}

/**
 * Picks up nearby passengers.
 */
function pickup()
{
    //1. detect passenger in range
    //loop through all the passenger lat/lng? Yes
    //Passengers = [{username:, name: house},{}] <-add lat/lng in Populate.
    
    //loop passengers, check if each are <15.0m in distance and and seat is empty
    //Distance calulation 
    var students_nearby = [];
    students_index = [];
    for (var i in PASSENGERS){
        //getgeometry() for lat lng?
        var d = shuttle.distance(PASSENGERS[i]["lat"], PASSENGERS[i]["lng"]); 
        if(d < 15){
            students_nearby.push(PASSENGERS[i]);
            students_index.push(i);
        }
    }
    
    //set next avail seat as passenger name for each student nearby
    //2. Add passenger to shuttle
    if(students_nearby.length > 0){
        for (var i in students_nearby){
            if(seats_available > 0 && PASSENGERS[students_index[i]]["picked_up"] == false){
                
                //5. Display passenger on shuttle list
                //add to next null
                for(var j in shuttle.seats){
                    if(shuttle.seats[j] == null){
                        shuttle.seats[j] = students_nearby[i]["name"];
                        break;
                    }
                }
                //shuttle.seats[SEATS - seats_available] = students_nearby[i]["name"];
                $("#announcements").html("Student added.");
                chart();
                seats_available -= 1; 
                //set passenger_pickup_status to true if picked up and exclude from boarding 
                PASSENGERS[students_index[i]]["picked_up"] = true;
                //3. Remove placemark 
                var features = earth.getFeatures();
                var p = students_nearby[i]["placemark"]
                features.removeChild(p);
                //4. Remove marker
                var m = students_nearby[i]["marker"]
                m.setMap(null);
                
            }
            else if (seats_available == 0){
                $("#announcements").html("All seats are filled!");
            }
        }
    }else{
        $("#announcements").html("No students within 15m.");
    }
    
}

/**
 * Populates Earth with passengers and houses.
 */
function populate()
{
    // mark houses
    for (var house in HOUSES)
    {
        // plant house on map
        new google.maps.Marker({
            icon: "https://google-maps-icons.googlecode.com/files/home.png",
            map: map,
            position: new google.maps.LatLng(HOUSES[house].lat, HOUSES[house].lng),
            title: house
        });
    }

    // get current URL, sans any filename
    var url = window.location.href.substring(0, (window.location.href.lastIndexOf("/")) + 1);

    // scatter passengers
    for (var i = 0; i < PASSENGERS.length; i++)
    {
        // pick a random building
        var building = BUILDINGS[Math.floor(Math.random() * BUILDINGS.length)];

        // prepare placemark
        var placemark = earth.createPlacemark("");
        placemark.setName(PASSENGERS[i].name + " to " + PASSENGERS[i].house);

        // prepare icon
        var icon = earth.createIcon("");
        icon.setHref(url + "/img/" + PASSENGERS[i].username + ".jpg");

        // prepare style
        var style = earth.createStyle("");
        style.getIconStyle().setIcon(icon);
        style.getIconStyle().setScale(4.0);

        // prepare stylemap
        var styleMap = earth.createStyleMap("");
        styleMap.setNormalStyle(style);
        styleMap.setHighlightStyle(style);

        // associate stylemap with placemark
        placemark.setStyleSelector(styleMap);

        // prepare point
        var point = earth.createPoint("");
        point.setAltitudeMode(earth.ALTITUDE_RELATIVE_TO_GROUND);
        //at lat & long to random building's lat lng
        point.setLatitude(building.lat);
        point.setLongitude(building.lng);
        point.setAltitude(0.0);

        // associate placemark with point
        placemark.setGeometry(point);

        // add placemark to Earth
        earth.getFeatures().appendChild(placemark);

        // add marker to map
        var marker = new google.maps.Marker({
            icon: "https://maps.gstatic.com/intl/en_us/mapfiles/ms/micons/man.png",
            map: map,
            position: new google.maps.LatLng(building.lat, building.lng),
            title: PASSENGERS[i].name + " at " + building.name
        });

        // TODO: remember passenger's placemark and marker for pick-up's sake
        //add lat and lng for each student added
        PASSENGERS[i]["lat"] = building.lat;
        PASSENGERS[i]["lng"] = building.lng;
        PASSENGERS[i]["placemark"] = placemark;
        PASSENGERS[i]["marker"] = marker;
        PASSENGERS[i]["picked_up"] = false;
        
        
        var destination = PASSENGERS[i]["house"];
        if (destination == "Thayer Hall" || destination == "Wigglesworth Hall"){
            //remove from map since freshmen
            earth.getFeatures().removeChild(placemark);
            marker.setMap(null);
        }else{
            PASSENGERS[i]["final_lat"] = HOUSES[destination]["lat"];
            PASSENGERS[i]["final_lng"] = HOUSES[destination]["lng"]
        }
    }
}
/**
 * Handler for Earth's viewchange event.
 */
function viewchange() 
{
    // keep map centered on shuttle's marker
    var latlng = new google.maps.LatLng(shuttle.position.latitude, shuttle.position.longitude);
    map.setCenter(latlng);
    bus.setPosition(latlng);
}

/**
 * Unloads Earth.
 */
function unload()
{
    google.earth.removeEventListener(earth.getView(), "viewchange", viewchange);
    google.earth.removeEventListener(earth, "frameend", frameend);
}

//EXTRA FEATURES
//TIMER COUNTDOWN.
var timeoutID;
var intervalID;
var currenttime = 300;
var timer_off = true;
function timer(){
    //timer ends in 5 min 3000000
    if(timer_off){
        timeoutID = window.setTimeout(endTimerAlert, 300000);
        intervalID = window.setInterval(countdown, 1000);
        timer_off = false;
    }
}
function endTimerAlert(){
    $("#current_time").html("Times up!");
    clearInterval(intervalID);
    currenttime = 300;
    timer_off = true;
}

function countdown(){
    currenttime -= 1; 
    $("#current_time").html(currenttime + " seconds left!");
}
//ADJUSTABLE VELOCITY
function setspeed(){
    shuttle.velocity = $("#speed").val();
}
//ADJUSTABLE CAPACITY
function setsize(){
    var new_seats = $("#size").val();
    seats_available = new_seats;
    shuttle.seats = [];
    for (var i = 0; i < new_seats; i++)
    {
        shuttle.seats[i] = null;
    }
    
    chart();
}
//maybe - HIGHLIGHT HOUSE if desination & HIGHLIGHT NAMES with matching color. nah need diff color picscd


