<form action="sell.php" method="post">
    <fieldset>
        <div class="form-group">
            <select autofocus class="form-control" name="symbol">
                <option value=""> </option>
                <?php foreach ($symbols as $symbol): ?>
                <option value="<?= $symbol ?>"><?= $symbol ?></option>
                <?php endforeach ?>
            </select>
        </div>
        <div class="form-group">
            <button type="submit" class="btn btn-default">Submit</button>
        </div>
    </fieldset>
</form>
