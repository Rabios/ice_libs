function loadsite() {
  function rand_i(n) {
    var rf = Math.random();
    var r = (rf * n);
    var f = Math.floor(r);
    
    return f;
  }
  
  function quote_str(s) {
    return ("\"" + s + "\"");
  }

  function get_slashes(s) {
    var res = 0;

    for (var i = 0; i < s.length; i++) {
      var char = s[i];
      if (char == '\\' || char == '/') res++;
    }

    return res;
  }

  function get_root(s) {
    var res = "";
    var slashes = get_slashes(s);
    var slash_count = 0;
    
    for (var i = 0; i < s.length; i++) {
      var char = s[i];

      if (char == '\\' || char == '/') {
        slash_count++;

        if (slash_count == slashes) {
          for (var j = i + 1; j < s.length; j++) {
            res += s[j];
          }

          break;
        }
      }
    }

    return res;
  }

  function scroll_y() {
    var res = window.pageYOffset;
    if (typeof(res) !== "undefined") return res;

    res = document.documentElement;
    if (typeof(res.clientHeight) != "undefined") return res.scrollTop;

    res = document.body.scrollTop;
    return res;
  }
  
  function set_rand_quote() {
    var quotes = [
      { text: "A book must be an ice axe to break the seas frozen inside our soul", author: "Franz Kafka" },
      { text: "You must have your heart on fire and your brain on ice", author: "Vladimir Lenin" },
      { text: "Thou art all ice. Thy kindness freezes", author: "William Shakespeare" },
      { text: "Ice and iron cannot be welded", author: "Robert Louis Stevenson" },
      { text: "Eternity is a glorious word, but eternity is ice", author: "Dejan Stojanovic" },
      { text: "Even the strongest blizzards start with a single snowflake", author: "Sara Raasch" },
      { text: "Every snowflake is unique, yet they are each perfect", author: "Donald L. Hicks" },
      { text: "Be thou as chaste as ice, as pure as snow, thou shalt not escape calumny", author: "William Shakespeare" },
      { text: "Civilization is like a thin layer of ice upon a deep ocean of chaos and darkness", author: "Werner Herzog" }
    ];
    
    var p = document.getElementById("quote");
    var rand_idx = rand_i(quotes.length - 1);
    var qotd = quotes[rand_idx];
    var tq = quote_str(qotd.text);
    
    p.innerHTML = tq + " - " + qotd.author;
  }

  var root = get_root(window.location.href);
  console.log(root);

  if (root == "index.html") {
    set_rand_quote();
  } else if (root == "docs.html") {
    var doco1 = document.getElementsByClassName('doco1')[0];
    doco1.style.height = (window.innerHeight + 10) + 'px';
    
    window.onscroll = function(ev) {
      doco1.focus();
      doco1.style.top = scroll_y() + "px";
      ev.preventDefault();
    };
  }
}
