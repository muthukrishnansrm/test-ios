<script src="https://code.jquery.com/jquery-1.9.1.min.js"></script>
<script type="text/javascript">
 
//alert("Out");
$(document).ready(function(){

$(document).ready(function ()
 {
		   	    		var url2 = (window.location.search).replace("?", "");
							
						$.ajax({
		
							headers: {"Content-Type": "application/x-www-form-urlencoded" },
							type: "POST",
							url: "https://pub.orcid.org/oauth/token",
							data : "client_id=APP-056GSP3J5RDS9KCM&client_secret=f5fcc22e-bd05-4c58-88c3-92d02be078dd&grant_type=authorization_code&redirect_uri=http://localhost/drupal/examples/example/&"+url2,
							success: OnSuccessone,
							error: function (error) {
									//alert(url2);
									//console.log(error);
								}
						}); 
			
});

    	function OnSuccessone(response) {
			                    console.log(response);
								 var orcidid = response.orcid;
								//alert(orcidid);
								$.ajax({
										headers: {"Content-Type": "application/json; qs=3;charset=UTF-8"},
										type: "GET",
										url: "https://pub.orcid.org/v1.2/search/orcid-bio/?q=orcid:"+orcidid,
										dataType: "jsonp",
										success: OnSuccess,
										error: function (error) {
		                                
																}
									}); 
		
							}
		function OnSuccess(data) {
			                console.log(data);
							var orcid_id = data["orcid-search-results"]["orcid-search-result"][0]["orcid-profile"]["orcid-identifier"]["path"];
							
							var first_name = data["orcid-search-results"]["orcid-search-result"][0]["orcid-profile"]["orcid-bio"]["personal-details"]["given-names"]["value"];
							
							var last_name = data["orcid-search-results"]["orcid-search-result"][0]["orcid-profile"]["orcid-bio"]["personal-details"]["family-name"]["value"];
							
							alert(first_name);
							alert(last_name);
							alert(orcid_id);
							//alert(orcidid);
							/*try {
								var email_address = data["orcid-search-results"]["orcid-search-result"][0]["orcid-profile"]["orcid-bio"]["contact-details"]["email"][0]["value"];
				  	            
								$.ajax({
									url: "",
									type: "GET",
									data: {"email" : email_address},
									success: function (data) {
											//console.log(data);
										window.location.href = 'http://localhost/drupal';
												
									}
								});
					    
								}
							catch(err) {
								
								alert("Test");
								alert(orcid_id);
								 								 
								<?php 
								 
								  // $servername = "localhost";
								 //  $username = "root";
								 //  $password = "";
								 //  $dbname = "testdb";

								 		$conn = new mysqli('localhost', 'root', '', 'testdb');
									// Check connection
											if ($conn->connect_error) {
											die("Connection failed: " . $conn->connect_error);
										} 

									$sql = "SELECT mail FROM users Where name = 'admin'";
									//$result = $conn->query($sql);
									
									//echo json_encode($rows);
								 ?>
								
								//alert(test);
								alert("DOne");
										
								
									var name = data["orcid-search-results"]["orcid-search-result"][0]["orcid-profile"]["orcid-bio"]["personal-details"]["given-names"]["value"];
									//alert("Dear " +name+", Your Orcid email seems private. Please change it to public and login");
									var email_address = prompt("Dear " +name+", Your Orcid email seems private, Please enter your orcid email below and submit", "Please enter your orcid email address here");
									alert(email_address);
									if(/^\w+([\.-]?\w+)*@\w+([\.-]?\w+)*(\.\w{2,3})+$/.test(email_address))
										{
						  alert(email_address);
											$.ajax({
													url: "",
													type: "GET",
													data: {"email" : email_address, "username" : name },
													success: function (data) {
											
														window.location.href = 'http://localhost/drupal';
												
													}
												});
										}
									else{
								
										alert("Please enater valid email");
									}
						
					   		}*/
				
				
				 
						
			}

});

</script>