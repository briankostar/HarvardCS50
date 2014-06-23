<?php

    // configuration
    require("../includes/config.php"); 

    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        
        if (empty($_POST["symbol"]))
        {
            apologize("You must provide a valid symbol.");
        }
        
    
        $stock = lookup($_POST["symbol"]);
        if ($stock === false){
            apologize("You must provide a valid symbol.");
        }else{
        
            $symbol = $stock["symbol"];
            $name = $stock["name"];
            $price = $stock["price"];
            //num_for takes 1,2 or 4 arg. 1arg=no deci + ',' every 1000. 2nd arg= decimal
            $price = number_format($price, 2, '.', '');
        
            render("quote.php", ["title" => "Quote", "symbol" => $symbol, "name" => $name, "price" => $price]);
        }
        //print("Price : " . $s["price"]) format decimals
        
    }
    else{
        render("quote_form.php", ["title" => "Quote"]);
    }

?>
