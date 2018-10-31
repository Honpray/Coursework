<html>
<body>


<?php

$username = $password = "";
$nameErr = $passwordErr = "";


if ($_SERVER["REQUEST_METHOD"] == "POST") {
	if (empty($_POST["username"])) {
    	$nameErr = "Username is required!";
    	echo($nameErr."<br/>");
    	exit();
  	} else {
	  	$username = test_input($_POST["username"]);
	  }
	if (empty($_POST["password"])) {
    	$passwordErr = "Password is required!";
    	echo($passwordErr."<br/>");
		exit();
  	} else {
	  	$password = test_input($_POST["password"]);
	  }
}

function test_input($data) {
  $data = trim($data);
  $data = stripslashes($data);
  $data = htmlspecialchars($data);
  return $data;
}


//-------------------------------------------------register process

if(isset($_POST['register'])){
	$registerFile = fopen("password.txt", "a");
	if($registerFile == false){
		echo("Could not access password file");
		exit();
	}
	fputs($registerFile, "$username,$password\n");
	echo("New user ".$username." added!");
	exit();
}else{


//-------------------------------------------------login process


$passwordFile = fopen("password.txt", "r");
if($passwordFile == false){
	echo("Could not access password file");
	exit();
}else{
	
	$verificationComplete = 0;

	while(!feof($passwordFile) && !$verificationComplete){
		$line = fgets($passwordFile);
		$line = chop($line);
		$field = explode(",", $line);
		if($username == $field[0]){
			$verificationComplete = 1;
			if($password == $field[1]){
				echo("Welcome back ". $username. "!<br/>");
				
//-------------------------------------------------admin login
				
				if($username == "admin"){
					echo("Hey admin! Have a look at the user list:<br/>");
					$userlistFile = "password.txt";
					$showUserlist = fopen($userlistFile, "r");
					if($showUserlist == false){
						echo "There is something wrong with the User list<br/>";
						exit();
					}
					while(! feof($showUserlist)){
						$adminline = fgets($showUserlist);
						$adminline = chop($adminline);
						$adminfield = explode(",", $adminline);
						echo $adminfield[0]. "<br/>";
					}
					fclose($showUserlist);
				}
				
			}else{
				echo("Wrong password, please try again.");
			}
		}
		
	}
	if($verificationComplete == 0){
		echo("Username does not exist. Please register first.");
	}
}

}


?>


</body>
</html>
