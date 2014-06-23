<?php

    // configuration
    require("../includes/config.php"); 

    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        if (empty($_POST["symbol"]))
        {
            apologize("You must provide a valid symbol.");
        }
        //update user cash
        //value is stock symbol's price * owned shares
        $price = lookup($_POST["symbol"])['price'];
        
        $shares = query("SELECT shares FROM Portfolio WHERE id = ? AND symbol = ?", $_SESSION["id"], $_POST["symbol"])[0]['shares'];
        
        $value = $price * $shares;
        query("UPDATE users SET cash = cash + ? WHERE id = ?", $value, $_SESSION["id"]);
        //remove symbol from portfolio.
        query("DELETE FROM Portfolio WHERE id = ? AND symbol = ?", $_SESSION["id"], $_POST["symbol"]);
        
        //update history
        //all the # of shares
        query("INSERT INTO History (id, type, symbol, shares, price) VALUES(?, ?, ?, ?, ?)", $_SESSION["id"], "SELL", $_POST["symbol"],  $shares, $price);
        redirect("/");
    }
    else{
        //load which stocks are avail to sell for this user from portfolio
        $rows = query("SELECT symbol FROM Portfolio WHERE id = ?", $_SESSION["id"]);
        //query returns array of asso. arrays for each matching query
        $symbols = [];
        foreach ($rows as $row){
            $symbols[] = $row['symbol'];
        }
        render("sell_form.php", ["title" => "Sell", "symbols" => $symbols]);
    }

?>
