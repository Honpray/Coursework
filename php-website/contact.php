<h2 id="contact">Contact Us</h2>

		<?php
			$filename = "contact.txt";
			$file = fopen($filename, "r");
			if($file == false){
				echo "There is something wrong with the Contact Information";
				exit();
			}
			//$filesize = filesize($filename);
			//$filecontent = fgets($file, $filesize);
			while(! feof($file)){
				echo fgets($file). "<br/>";
			}
			fclose($file);
		?>
