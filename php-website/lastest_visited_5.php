<div>
	<!-- <a href=""><h2>last five previously visited products</h2></a><br/> -->
	<?php
		if (!isset($_COOKIE["count1"])){$_COOKIE["count1"] = 0;
		}
		if (!isset($_COOKIE["count2"])){$_COOKIE["count2"] = 0;
		}
		if (!isset($_COOKIE["count3"])){$_COOKIE["count3"] = 0;
		}
		if (!isset($_COOKIE["count4"])){$_COOKIE["count4"] = 0;
		}
		if (!isset($_COOKIE["count5"])){$_COOKIE["count5"] = 0;
		}
		if (!isset($_COOKIE["count6"])){$_COOKIE["count6"] = 0;
		}
		if (!isset($_COOKIE["count7"])){$_COOKIE["count7"] = 0;
		}
		if (!isset($_COOKIE["count8"])){$_COOKIE["count8"] = 0;
		}
		if (!isset($_COOKIE["count9"])){$_COOKIE["count9"] = 0;
		}
		if (!isset($_COOKIE["count10"])){$_COOKIE["count10"] = 0;
		}

		if (!isset($_COOKIE["time_visited1"])){$_COOKIE["time_visited1"] = 0;
		}
		if (!isset($_COOKIE["time_visited2"])){$_COOKIE["time_visited2"] = 0;
		}
		if (!isset($_COOKIE["time_visited3"])){$_COOKIE["time_visited3"] = 0;
		}
		if (!isset($_COOKIE["time_visited4"])){$_COOKIE["time_visited4"] = 0;
		}
		if (!isset($_COOKIE["time_visited5"])){$_COOKIE["time_visited5"] = 0;
		}
		if (!isset($_COOKIE["time_visited6"])){$_COOKIE["time_visited6"] = 0;
		}
		if (!isset($_COOKIE["time_visited7"])){$_COOKIE["time_visited7"] = 0;
		}
		if (!isset($_COOKIE["time_visited8"])){$_COOKIE["time_visited8"] = 0;
		}
		if (!isset($_COOKIE["time_visited9"])){$_COOKIE["time_visited9"] = 0;
		}
		if (!isset($_COOKIE["time_visited10"])){$_COOKIE["time_visited10"] = 0;
		}

		
		$time_array = array("1" => $_COOKIE["time_visited1"],
						  "2" => $_COOKIE["time_visited2"],
						  "3" => $_COOKIE["time_visited3"],
						  "4" => $_COOKIE["time_visited4"],
						  "5" => $_COOKIE["time_visited5"],
						  "6" => $_COOKIE["time_visited6"],
						  "7" => $_COOKIE["time_visited7"],
						  "8" => $_COOKIE["time_visited8"],
						  "9" => $_COOKIE["time_visited9"],
						  "10" => $_COOKIE["time_visited10"]
						);
		arsort($time_array);
		$top_five_time_array = array_slice($time_array, 0, 5, true);
		echo("<h2>last five previously visited products</h2>");
		foreach( $top_five_time_array as $key => $value ){
			if($value!=0){
				echo "<h3>Website No.".$key." was last visited at ";
				echo date("m/d/Y h:i:s a", $value);
				echo " (UTC)</h3><br/>";
				include("services/$key.php");
			}else{
				echo "Not visited yet!&nbsp&nbsp Click the link to pay the very first visit!<br/>";
			}
			
		}
	?>
</div>
