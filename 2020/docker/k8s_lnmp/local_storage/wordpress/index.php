<?php
$con = mysqli_connect(getenv('WORDPRESS_DB_HOST'), "root", getenv('WORDPRESS_DB_PASSWORD'), "mysql");
if (mysqli_connect_errno()) {
    printf("connection failed: %s\n", mysqli_connect_error());
    exit();
}
$query = "SELECT VERSION()";
$res = mysqli_query($con, $query);
if ($res) {
    $row = mysqli_fetch_row($res);
    echo $row[0];
}
mysqli_free_result($res);
mysqli_close($con);
phpinfo();
