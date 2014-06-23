<div>
    <!--<img alt="Under Construction" src="/img/construction.gif"/>-->
</div>
<table class="table table-striped" style="text-align: left">
<thead>
    <tr>
        <th>Type</th>
        <th>Date/Time</th>
        <th>Symbol</th>
        <th>Shares</th>
        <th>Price</th>
    </tr>
</thead>
<tbody>
<?php foreach ($rows as $row): ?>

    <tr>
        <td><?= $row["type"] ?></td>
        <td><?= $row["datetime"] ?></td>
        <td><?= $row["symbol"] ?></td>
        <td><?= $row["shares"] ?></td>
        <td><?= number_format($row["price"], 2, ".", "") ?></td>
    </tr>

<?php endforeach ?>
</tbody>
</table>
