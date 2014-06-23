<?php

    // configuration
    require("../includes/config.php"); 
    //get data from history table and populate it.
    $rows = query("SELECT type, datetime, symbol, shares, price FROM History WHERE id = ?", $_SESSION["id"]);
    //should format datetime and price
    foreach ($rows as $row){
        $row["price"] = 5;//number_format($row["price"], 2, ".", "");
        //dump($row["price"]);
    }
    
    render("history.php", ["title" => "History", "rows" => $rows]);
    
?>
