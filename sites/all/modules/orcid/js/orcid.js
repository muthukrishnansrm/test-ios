$(document).ready(function () { alert("Hello!"); 
		   	    		var url2 = (window.location.search).replace("?", "");
						//alert(url2);
	
						$.ajax({
		
							headers: {"Content-Type": "application/x-www-form-urlencoded" },
							type: "POST",
							url: "https://pub.orcid.org/oauth/token",
							data : "client_id=APP-056GSP3J5RDS9KCM&client_secret=f5fcc22e-bd05-4c58-88c3-92d02be078dd&grant_type=authorization_code&redirect_uri=http://localhost/drupal/examples/example/&"+url2,
	
							success: function (response) {
								var orcidid = response.orcid;
								console.log(response);
								$.ajax({
										headers: {"Content-Type": "application/json; qs=3;charset=UTF-8"},
										type: "GET",
										url: "https://pub.orcid.org/v1.2/search/orcid-bio/?q=orcid:"+orcidid,
										dataType: "jsonp",
										//data: JSON.stringify(this),
										success: function (data) {
											console.log(data);
											// console.log(JSON.stringify({duration: data}));
											//  console.log(JSON.stringify(data.personal-details)); 
											// console.dir(data);
											// console.log(data);
				
		
										},
										error: function (error) {
		
											alert("Failed");
											console.log(error);
										}
									}); 
		
								//   alert(response.access_token);
								//   alert(response.orcid);
								// console.log(response);
							},
							error: function (error) {
									//alert(url2);
									console.log(error);
								}
						}); 
		   
		   
				});