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
							var name = data["orcid-search-results"]["orcid-search-result"][0]["orcid-profile"]["orcid-identifier"]["path"];
							alert(name);
							alert(orcid_id);
							//alert(orcidid);
						/*	try {
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
								 
								//var mysql = require("mysql");
								//var con = mysql.createConnection({host: "localhost",user: "root",password: "",database: "testdb"});
								//alert("test with database");
								//con.query('SELECT * FROM users',function(err,rows){
								//if(err) throw err;
								//console.log('Data received from Db:\n');
								//console.log(rows);
										
								
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
													data: {"email" : email_address},
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