<?php

    // configuration
    require("../includes/config.php"); 

    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        if (empty($_POST["symbol"]))
        {
            apologize("You must provide a valid symbol.");
        }
        if (empty($_POST["number"]))
        {
            apologize("You must provide #of shares to buy!.");
        }
        //check if symbol exist
        $symbol = strtoupper($_POST["symbol"]);
        $share = lookup($symbol);
        if ($share == false){
            apologize("That symbol doesn't exist!");
        }
        
        //get user cash amount, see if its < share price * value
        $price = $share['price'];
        $purchase_value = $price * $_POST["number"];
        $user_cash = query("SELECT cash FROM users WHERE id = ?", $_SESSION["id"])[0]["cash"];
        
        if ($user_cash < $purchase_value){
            apologize("You do not have enough cash!");
        }
        else
        {
            //update users's cash. - cash used
            query("UPDATE users SET cash = cash - ? WHERE id = ?", $purchase_value, $_SESSION["id"]);
            //update portfolio. if no conflict, add, if conflict, update
            query("INSERT INTO Portfolio (id, symbol, shares) VALUES(?, ?, ?) ON DUPLICATE KEY UPDATE shares = shares + VALUES(shares)", $_SESSION["id"], $symbol, $_POST["number"]);
            //update history table
            query("INSERT INTO History (id, type, symbol, shares, price) VALUES(?, ?, ?, ?, ?)", $_SESSION["id"], "BUY", $symbol,  $_POST["number"], $price);
        }
        
        redirect("/");
    }
    else{
        
        render("buy_form.php", ["title" => "Buy"]);
    }

?>
