<?php

    // configuration
    require("../includes/config.php");

    // if form was submitted
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // validate registration
        //check if current pass provided
        if (empty($_POST["cur_pass"]))
        {
            apologize("You must provide your current password");
        }
        //check new password provided
        if (empty($_POST["new_pass"]))
        {
            apologize("You must write a new password.");
        }
        //check if password matches confirmation
        if ($_POST["new_pass"] == ($_POST["new_pass_confirm"]))
        {
            //insert to database
            $result = query("UPDATE users SET hash = ? WHERE id = ?", crypt($_POST["new_pass"]),$_SESSION["id"]);
            //query returns false if insert(user already exist) fails so check for this
            if ($result === false){
                apologize("Registration failed.");
            }else{
                redirect("/");
            }
        }else{
            apologize("You new password does not match!");
        }
    }
    else
    {
        // else render form
        render("passreset_form.php", ["title" => "Password Reset"]);
    }

?>
