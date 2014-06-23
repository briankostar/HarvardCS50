<?php

    // configuration
    require("../includes/config.php");

    // if form was submitted
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // validate registration
        //check if username provided
        if (empty($_POST["username"]))
        {
            apologize("You must provide your username.");
        }
        if (empty($_POST["email"]))
        {
            apologize("You must provide your email.");
        }
        //check password provided
        if (empty($_POST["password"]))
        {
            apologize("You must provide a password.");
        }
        //check if password matches confirmation
        if ($_POST["password"] == ($_POST["confirmation"]))
        {
            //insert to database
            $result = query("INSERT INTO users (username, hash, cash, email) VALUES(?, ?, 10000.00, ?)", $_POST["username"], crypt($_POST["password"]), $_POST["email"]);
            //query returns false if insert(user already exist) fails so check for this
            //dump($result);
            if ($result === false){
                apologize("Registration failed. Check Username/Email.");
            }else{
                //login
                //select id 
                //this returns the row of the last insert
                $rows = query("SELECT LAST_INSERT_ID() AS id");
                //get the id, which is the first element of the rows array
                $id = $rows[0]["id"];
                //store id in the session, which is logging them in.
                $_SESSION["id"] = $id;
                //redirect to home, logged in
                redirect("/");
            }
        }else{
            apologize("You must provide a matching password.");
        }
        
        
        
    }
    else
    {
        // else render form
        render("register_form.php", ["title" => "Register"]);
    }

?>
