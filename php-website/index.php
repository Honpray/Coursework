<!DOCTYPE html>
<html>
	<head>
		<title>Serious Bay</title>
		<link rel="shortcut icon" type="image/x-icon" href="~/favicon.ico"/>
		<link rel="stylesheet" href="style.css" />
		<style>
			* {
				line-height: 140%;
			}
			h1 {
				text-align: center;
				font-family: "Goudy Old Style", Garamond, "Big Caslon", "Times New Roman", serif;
			}
			.loginform{
				text-align: center;
			}
			body{background-color: floralwhite; width:600px;margin:20px auto;}
			.footer {
				position: fixed;
				left: 0;
				bottom: 20px;
				width: 100%;
				text-align: center;
			}
			#copy {
				font-style: italic;
				color: gray;
				font-size: small
			}
		</style>
	</head>
	<body>
		<h1>Serious Bay</h1>
		<p>A Serious search engine. Aimed to save your time on searching the right software for users.</p>
		<form class="loginform" method="post" action="password.php">
			Username:<input type="text" name="username" placeholder="Mary Smith" required>&nbsp
			Password:<input type="password" name="password" placeholder="123456" required>&nbsp
			<input type="submit" name="register" value="Register">&nbsp
			<input type="submit" name="login" value="Login">
		</form>
		
		<input class="burger-check" id="burger-check" type="checkbox"><label for="burger-check" class="burger"></label>
		<nav id="navigation1" class="navigation">
		  <ul>
		    <li><a href="home.php">Home</a></li>
		    <li><a href="about.php">About</a></li>
		    <li><a href="services.php">Services</a></li>
		    <li><a href="news.php">News</a></li>
		    <li><a href="contact.php">Contacts</a></li>
		    <li><a href="users_tab.php">Users(MySQL)</a></li>
		  </ul>
		</nav>
		
		
		<footer class="footer">
			<p id="copy">&copy 2017 SERIOUS BAY ALL RIGHT RESERVED</p>
		</footer>
		
		
		 
	</body>
</html>
