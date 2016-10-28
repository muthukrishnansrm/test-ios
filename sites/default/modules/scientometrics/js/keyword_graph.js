var D_SVG_DIV;
var q_controls;
var d_app;
(function($){
		Drupal.behaviors.scientometrics = {
  			attach: function (context, settings) {
  				$('#content').html("");
  				globalContext = context;
  				var text = '<div align="center"><div style="vertical-align:middle; display:inline;font-size: x-large;padding-left: 10px;">Keyword Graph for Journal of Intelligent and Fuzzy Systems Keywords</div></div>'
  				text += '<div id="loading" style="width: 100%; height: 100vh;"><img src="http://fuzzyinsights.com/sites/default/files/loading.gif" style="margin-left: auto; margin-right: auto; display: block; margin-top: 30vh;"><p style="text-align:center">Creating Links. Please wait..</p></div>'
  				text += '<div id="app" style="display:none">'
  				text += '<div id="sciento_app"></div>'
  				text += '<div id="side-bar">Filter By Year:<select id="filter_by_year" onchange="query_papers(this.value, load_graph)"></select><p id="article-title" style="font-size: 2.0vw;"></p> <p id="authors" style="font-size: 2.0vw;"></p></div></div>'
    			$('#content', context).append(text);
    			d_app = $('#sciento_app')[0];
    			$('#sciento_app').html("");
    			var q_controls = $('<div></div>').appendTo(d_app);
    			D_SVG_DIV = $('<div></div>').appendTo(d_app).get(0);
  			}
		};
})(jQuery);

Sparql.config({
        mode: 'global',
        alias: '$$'
    });
    $$.endpoint("http://lod.fuzzyinsights.com:3030/fuzzyinsights-beta/");

// declare prefixes
    $$.prefix({
        'rdfs': 'http://www.w3.org/2000/01/rdf-schema#',
        'dcterms': 'http://purl.org/dc/terms/',
        'foaf': 'http://xmlns.com/foaf/0.1/'
    });

    var A_CONFERENCES = [];
    var H_FULLKEYWORDS = {};
    load_sciento_keywords();
    function load_sciento_keywords() {
        // var d_app = $('#sciento_app')[0];
        // $('#sciento_app').html("");
        // console.log($('#sciento_app'));
        
        // var q_controls = $('<div></div>').appendTo(d_app);
        // $('#article-title').appendTo(d_app);
        // $('#authors').appendTo(d_app);

        // D_SVG_DIV = $('<div></div>').appendTo(d_app).get(0);


        add_searching(d_app);
      //   $$('?paper dcterms:created ?year')
    		// .select('?year')
   	 	// 	.order('?year')
    		// .results(function(year) {
    		// 	console.log(year);
    		// });
    	var query_year_url = "http://lod.fuzzyinsights.com:3030/fuzzyinsights-beta/query?query=PREFIX+dcterms%3A+%3Chttp%3A%2F%2Fpurl.org%2Fdc%2Fterms%2F%3E%0D%0APREFIX+rdfs%3A+%3Chttp%3A%2F%2Fwww.w3.org%2F2000%2F01%2Frdf-schema%23%3E%0D%0APREFIX+foaf%3A+%3Chttp%3A%2F%2Fxmlns.com%2Ffoaf%2F0.1%2F%3E%0D%0ASELECT+%3Fyear+where%7B%0D%0A%3Fpaper+dcterms%3Acreated+%3Fyear%0D%0A%7Dgroup+by+%3Fyear+order+by+%28%3Fyear%29"
	  	$.ajax({
      		type: "GET",
      		url: query_year_url,
      		dataType: "json",
      		success: function(data) {
      			// console.log(data);
      			// console.log(data.results.bindings[0].year.value);
      			// console.log(data.results.bindings);
  				query_papers(data.results.bindings[data.results.bindings.length-1].year.value, load_graph);
  				var year_filter = document.getElementById('filter_by_year');
  				var selectIndex = 0;
      			data.results.bindings.forEach(function (y_array){
      				if(y_array.year.value > 2000){
      					var option = document.createElement('option');
	  					option.innerHTML = y_array.year.value;
	  					year_filter.appendChild(option);
	  					selectIndex = selectIndex+1;
                        // console.log(selectIndex);
	  				}
      			});
      			year_filter.selectedIndex = selectIndex-1;
      		},
      		error: function(a,b,c) {
          		alert("error");
    		}

      	});
        // query_papers(load_graph);
        // $('<div class="keywordyear"></div>')
        //     .click(function() {
        //         query_papers();
        //     })
        //     .appendTo(q_controls);
    };

var s = {};
    function query_papers(article_year, f_okay) {
        document.getElementById('loading').style.display = "block";
        document.getElementById('app').style.display = "none";
    	$('#article-title').empty();
    	$('#authors').empty();
        $$('?paper dcterms:subject ?keyword. ?paper rdfs:label ?title. ?paper dcterms:created '+article_year)
            .select('?paper ?title ?keyword')
            .results(function(a_res) {
            s= a_res;
            // console.info(a_res);
                // console.log(response);
            var h_papers = {};
            a_res.forEach(function(h_row) {
                var s_uri = h_row.paper.value;
                var h_paper = h_papers[s_uri];
                if(!h_paper) {
                    h_paper = h_papers[s_uri] = {
                        paper: h_row.paper.value,
                        title: h_row.title.value,
                        keywords: [],
                        links: 0,
                    };
                }
                var keyword = h_row.keyword.value.toLowerCase();
                        keyword = keyword.split(", ");
                        
                h_paper.keywords = keyword;
            });
            var a_papers = [];
            Object.keys(h_papers).forEach(function(s_key) {
                // console.log(s_key);
                $$('?paper dcterms:subject ?fullkeyword')
                    .select('?paper ?fullkeyword')
                    .values({
                        paper: ['<'+s_key+'>'],
                    })
                    .results(function(a_res) {
                        // console.log(a_res);
                        a_res.forEach(function(h_row) {
                        var s_paper_id = h_row.paper.value;
                        var a_fullkeywords = H_FULLKEYWORDS[s_paper_id];
                        if(!a_fullkeywords) a_fullkeywords = H_FULLKEYWORDS[s_paper_id] = [];

                        var s_fullkeyword = h_row.fullkeyword.value;
                        var keyword = s_fullkeyword.toLowerCase();
                        keyword = keyword.split(", ");
                        a_fullkeywords = keyword;
                        // console.log(a_fullkeywords);
                    });
                });
                var h_paper = h_papers[s_key];
                a_papers.push(h_paper);
                // console.log(a_papers);
            });
            var a_links = match_keywords(a_papers);


            for(var i=0; i<a_links.length; i++) {
                var h_link = a_links[i];
                a_papers[h_link.source].links += 1;
                a_papers[h_link.target].links += 1;
            }

            a_papers.forEach(function(h_paper) {
                h_paper.weight = 1 / h_paper.links;
            });

          // construct force graph
            f_okay(a_papers, a_links);
            
        });
    }
    function match_keywords(a_papers) {
        
        // cache array length
        var n_keys = a_papers.length;

        //
        var h_links = [];

        // n log(n) keyword-matching
        for(var i_left=0; i_left<n_keys-1; i_left++) {
        var a_keywords_left = a_papers[i_left].keywords;

        for(var i_right=i_left+1; i_right<n_keys; i_right++) {
            var a_keywords_right = a_papers[i_right].keywords;

            // count how many keywords match between this pair
            var c_matches = 0;

            // match keywords
            for(var i_keyword_left=0; i_keyword_left<a_keywords_left.length; i_keyword_left++) {
                for(var i_keyword_right=0; i_keyword_right<a_keywords_right.length; i_keyword_right++) {
          // found matching keyword!
                    if(a_keywords_left[i_keyword_left] === a_keywords_right[i_keyword_right]) {
                        c_matches += 1;
                        break;
                    }
                }
            }

            if(c_matches != 0) {
                //
                h_links.push({
                    source: i_left,
                    target: i_right,
                    value: c_matches,
                });
            }
        }
    }

    //
    return h_links;
    }
    
    function blank_app() {
        return $(D_SVG_DIV).empty().get(0);
    }

    function add_searching(d_app) {

    }

    function load_graph(h_nodes, h_links) {

        // 
        var width = 1024;
        var height = 600;
        // console.log("load graph");
        // 
        var svg = d3.select(blank_app()).append("div")
   .classed("svg-container", true) //container class to make it responsive
   .append("svg")
   //responsive SVG needs these 2 attributes and no width and height attr
   .attr("preserveAspectRatio", "xMinYMin meet")
   .attr("viewBox", "0 0 1000 800")
   //class to make it responsive
   .classed("svg-content-responsive", true); 
// var svg = d3.select(blank_app()).append('svg')
//     .attr('width', width)
//     .attr('height', height);
        // initialize tooltip
var tip = d3.tip().attr('class', 'keyword-node-title').html(function(d) {
    // var a_keywords_display = H_FULLKEYWORDS[d.paper];
    // console.log('H_FULLKEYWORDS['+d.paper+'] = ', H_FULLKEYWORDS[d.paper]);
    return d.links+' paper'+(d.links !== 1? 's': '')+' share'+(d.links === 1? 's': '')+' similar keywords<br />This paper has '+(d.keywords.length)+' keyword'+(d.keywords.length !== 1? 's': '')+': <br />&bull; '+d.keywords.join('<br />&bull; ');
  });
        // console.log(svg);
        // console.log(tip);
        svg.call(tip);


        // find maximum number of links any node has
        var max_links = d3.max(h_nodes, function(d) {
            return d.links;
        });

        // find maximum number of keywords any node has
        var max_keywords = d3.max(h_nodes, function(d) {
            return d.keywords.length;
        });


        // create color scale for num links
        var color = d3.scale.sqrt()
            .domain([0, max_links*Math.pow(0.5, 2), max_links])
            .range(['blue','white','red']);

        // create radius scale for num keywords
        var radius = d3.scale.sqrt()
            .domain([1, max_keywords])
            .range([2, 9]);


        //
        var force = d3.layout.force()
            .gravity(.2)
            .charge(-30)
            .linkDistance(55)
            .size([width, height])
            .nodes(h_nodes)
            .links(h_links)
            .start();

        //
        var link = svg.selectAll('.link')
            .data(h_links)
            .enter().append('line')
            .attr('class', 'link')
            .style('stroke-width', function(d) {
                return Math.sqrt(d.value);
            })
            .style('stroke', "black");

        var f_rdx = function(d) { return d.x };
        var f_rdy = function(d) { return d.y };

        //
        var node = svg.selectAll('.node')
            .data(h_nodes)
            .enter().append('circle')
            .attr('class', 'node')
            .attr('r', function(d) {
                return radius(d.keywords.length);
            })
            .style('fill', function(d, i) {
                return color(d.links);
            })
            .call(force.drag)
            .on('mouseover', function(d) {
                tip.show(d);
                var article_link = d.paper.replace("lod.", "");
                $('#article-title').empty();
                $('#article-title').html('<span style="font-size: larger;color: red";>Article Title: <br/><br/></span>')
                .append($('<a href="'+article_link+'" target="_blank">'+d.title+'</a>'));
                $$('<'+d.paper+'> dcterms:creator ?author. ?author foaf:name ?name')
                .select('?author ?name')
                .exec(function(a_rows) {
                    // console.log(a_rows);
                    $('#authors').empty()
                    .html('<span style="font-size: larger;color: red";>Authors: <br/></span>')
                    a_rows.forEach(function(h_row) {
                        var author_link = h_row.author.value.replace("lod.", "");
                        $('<a href="'+author_link+'" target="_blank">'+h_row.name.value+'<br/></a>').appendTo('#authors');
                    });
                });
            })
            .on('mouseout', tip.hide);



        //
        force.on('tick', function() {
        link
            .attr('x1', function(d) { return d.source.x; })
            .attr('y1', function(d) { return d.source.y; })
            .attr('x2', function(d) { return d.target.x; })
            .attr('y2', function(d) { return d.target.y; });
        node
            .attr('cx', function(d) { return d.x; })
            .attr('cy', function(d) { return d.y; });
        })


        // var legend = svg.selectAll('.legend')
        //  .data(color.domain().slice(0, max_links))
        //  .enter().append('g')
        //    .attr('class', 'legend')
        //    .attr('transform', function(d, i) {
        //      return 'translate(0,'+(i*20)+')';
        //    });

        // legend.append('rect')
        //  .attr('x', width-18)
        //  .attr('width', 18)
        //  .attr('height', 18)
        //  .style('fill', color);

          // legend.append('text')
          //  .attr('x', width-24)
          //  .attr('y', 9)
          //  .attr('dy', '0.35em')
          //  .style('text-anchor', 'end')
          //  .text(function(d, i) {
          //    return (i)+' links';
          //  });


          // // legend
          // var legend = svg.append('g')
          //  .attr('class', 'legend')
          //  .attr('transform', 'translate(50,30)')
          //  .style('font-size', '12px')
          //  .call(d3.legend);
        document.getElementById('loading').style.display = "none";
        document.getElementById('app').style.display = "block";
    }
