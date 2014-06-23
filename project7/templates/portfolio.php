<div>
    <!--<img alt="Under Construction" src="/img/construction.gif"/>-->
</div>
<table class="table table-striped" style="text-align: left">
<thead>
    <tr>
        <th>Symbol</th>
        <th>Name</th>
        <th># Shares</th>
        <th>Price</th>
        <th>Total Value</th>
    </tr>
</thead>
<tbody>
<?php foreach ($positions as $position): ?>

    <tr>
        <td><?= $position["symbol"] ?></td>
        <td><?= $position["name"] ?></td>
        <td><?= $position["shares"] ?></td>
        <td><?= $position["price"] ?></td>
        <td><?= $position["value"] ?></td>
    </tr>

<?php endforeach ?>
    <tr>
        <td colspan="4">Cash Remaining:</td>
        <td><?= $cash ?></td>
    </tr>
    <tr>
        <td colspan="4">Portfolio Value:</td>
        <td><?= $portfolio_value ?></td>
    </tr>
</tbody>
</table>
