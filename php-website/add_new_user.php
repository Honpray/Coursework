<html>
<head>
<title>Add New User</title>
</head>
<body>
<form action="" method="post">

<h3><b>Add a New User</b></h3>

<p>First Name:<br/>
<input type="text" name="first_name" size="30" value="" />
</p>

<p>Last Name:<br/>
<input type="text" name="last_name" size="30" value="" />
</p>

<p>Email:<br/>
<input type="text" name="email" size="30" value="" />
</p>

<p>Home Address:<br/>
<input type="text" name="address" size="30" value="" />
</p>

<p>Home Phone:<br/>
<input type="text" name="home_phone" size="30" value="" />
</p>

<p>Cell Phone:<br/>
<input type="text" name="cell_phone" size="30" value="" />
</p>

<p>
<input type="submit" name="submit" value="Submit" />
</p>

</form>

<?php
if(isset($_POST["submit"])){
	require_once(dirname(__FILE__). "\database_connect.php");
	$sql = "INSERT INTO `usertable` (`id`, `First Name`, `Last Name`, `Email`, `Home Address`, `Home Phone`, `Cell Phone`) VALUES (NULL, '".$_POST["first_name"]."', '".$_POST["last_name"]."', '".$_POST["email"]."', '".$_POST["address"]."', '".$_POST["home_phone"]."', '".$_POST["cell_phone"]."')";
	if ($conn->query($sql)) {
     echo "<script type= 'text/javascript'>alert('New Record Inserted Successfully');</script>";
	}else{
     echo "<script type= 'text/javascript'>alert('Data not successfully Inserted.');</script>";
	}
	$conn = null;
}

?>

</body>
</html>
