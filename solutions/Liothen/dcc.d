import std.net.curl, std.stdio, std.regex, std.string, std.algorithm, std.array, std.conv;

void main() {
	// Get HTML
	auto html         = get!HTTP("directus.darkscience.net:6789");	
	auto re           = regex(r"\d+");
	auto nums         = matchAll(html, re).map!(a => a.front.to!size_t).array();
	auto answer       = nums[1] * nums[2];
	
	// Post
	auto client = HTTP();
	client.addRequestHeader("Content-Type", "application/x-www-form-urlencoded");
	string postme	  = text("answer=", answer);
    auto post         = post("directus.darkscience.net:6789", postme, client);
    
    // Verify Correctness
    auto post_result = "";
    if (matchAll(post, r"\bCorrect\b")) {
    	post_result = "Correct!";
    } else {
    	post_result = "Wrong!";
    }

	// Print Results
	string response   = format("Problem is %s + %s = %s (%s)",nums[1],nums[2],answer,post_result);
	writeln(response);
}