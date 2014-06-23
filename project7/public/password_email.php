<?php

    // configuration
    require("../includes/config.php");
    require_once("PHPMailer/class.phpmailer.php");

    // if form was submitted
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        if (empty($_POST["email"]))
        {
            apologize("You must provide an email");
        }
        //check with database if email exists
        $rows = query("SELECT email FROM users WHERE email = ?", $_POST["email"]);
        //dump($rows);
        if($rows == false){
            apologize("Enter a valid email address");
        }
        //random pass
        $randomString = substr(str_shuffle("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890"), 0, 10);
        $encryptedPass = crypt($randomString);
        query("UPDATE users SET hash =? WHERE email = ?", $encryptedPass, $_POST["email"]);
         
        // instantiate mailer
        $mail = new PHPMailer();

        // use your ISP's SMTP server (e.g., smtp.fas.harvard.edu if on campus or smtp.comcast.net if off campus and your ISP is Comcast)
        //smtp.teksavvy.com
        $mail->IsSMTP();
        $mail->Host = "smtp.fas.harvard.edu";

        // set From:
        $mail->SetFrom("cs50@fiance.com");

        // set To:
        $mail->AddAddress($_POST["email"]);

        // set Subject:
        $mail->Subject = "CS50 Password Reset";

        // set body
        $mail->Body = "Hello, your new password is : " . $randomString;

        // send mail
        if ($mail->Send() === false){
            die($mail->ErrorInfo . "\n");
        }
        render("pass_confirm.php", ["title" => "Password Reset"]);
        }
        
    else
    {
        // else render form
        render("forgotpass_form.php", ["title" => "Password Reset"]);
    }

?>
