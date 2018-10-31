<?php
// windows path
 
// php search data in mysql database using PDO
// set data in input text

$id = "";
$first_name = "";
$last_name = "";
$phone = "";

if(isset($_POST['submit']))
{
    // connect to mysql
	require_once(dirname(__FILE__). "\database_connect.php");

    // id to search
    $id = $_POST['id'];
    
    // mysql search query
    $pdoQuery = "SELECT * FROM users WHERE id = :id";
    
    $pdoResult = $conn->prepare($pdoQuery);
    
    //set your id to the query id
    $pdoExec = $pdoResult->execute(array(":id"=>$id));
    
    if($pdoExec)
    {
        // if id exist 
        // show data in inputs
        if($pdoResult->rowCount()>0)
        {
            foreach($pdoResult as $row)
            {
                $id = $row['id'];
                $fname = $row['first_name'];
                $lname = $row['last_name'];
                $age = $row['phone'];
            }
        }
            // if the id not exist
            // show a message and clear inputs
        else{
            echo 'No Data With This ID';
        }
    }else{
        echo 'ERROR Data Not Inserted';
    }
}


?>

<html>
<head>
<title>Search by Names | Email | Phone Numbers</title>
</head>

<body>
<form action="php_search_in_mysql_database_using_pdo.php" method="post">
ID:<br/>
<input type="text" name="id" value=""><br/>
First Name:<br/>
<input type="text" name="first_name" value=""><br/>
Last Name:<br/>
<input type="text" name="last_name" value=""><br/>
Phone Number:<br/>
<input type="text" name="phone" value=""><br/>
<input type="submit" name="submit" value="Search">
</form>

</body>
</html>
