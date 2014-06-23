<?php

    // configuration
    require("../includes/config.php"); 

    //query for this user
    $rows = query("SELECT symbol, shares FROM Portfolio WHERE id = ?", $_SESSION["id"]);
    
    //rows is {{symbol:goog, shares: 10},{}}
    //get what stocks, how many, its value, cash balance and send to portfolio. make array of rows
    $positions = [];
    
    foreach ($rows as $row)
    {
        $stock = lookup($row["symbol"]);
        if ($stock !== false)
        {
            $positions[] = [
                "symbol" => $row["symbol"],
                "name" => $stock["name"],
                "shares" => $row["shares"],
                "price" => $stock["price"],
                "value" => number_format(($row["shares"] * $stock["price"]), 2, '.', '')
            ];
            
        }
        
    }
    
    $cash = query("SELECT cash FROM users WHERE id = ?", $_SESSION["id"]);
    $cash = number_format($cash[0]["cash"], 2, '.', '');
    
    $stock_value = 0;
    foreach ($positions as $pos){
        $stock_value = $stock_value + $pos["value"];
    }
    $portfolio_value = $stock_value + $cash;
    $portfolio_value = number_format($portfolio_value, 2, '.', '');
    
    render("portfolio.php", ["title" => "Portfolio", "positions" => $positions, "cash" => $cash, "portfolio_value" => $portfolio_value]);

?>
