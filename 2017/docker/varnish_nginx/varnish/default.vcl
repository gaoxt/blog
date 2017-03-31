vcl 4.0;
import directors;

//探针，每1秒检查一次，超时1秒超过2次以上有1次通过，则视为健康，否则不健康。
probe healthche {
    .url="/";
    .timeout = 1s;
    .interval = 1s;
    .window = 2;
    .threshold = 1;
}

backend server1 {
    .host = "nginx1";
    .port = "80";
    .probe = healthche ;
}

backend server2 {
    .host = "nginx2";
    .port = "80";
    .probe = healthche ;
}

sub vcl_init {
    new cluster = directors.round_robin();
    cluster.add_backend(server1);
    cluster.add_backend(server2);
}

sub vcl_recv{
    if (req.restarts == 0) {
        if (req.http.X-Fowarded-For) {
            set req.http.X-Forwarded-For = req.http.X-Forwarded-For + "," + client.ip;
        } else {
            set req.http.X-Forwarded-For = client.ip;
        }
    }

    if (req.method == "PURGE") {
        ban("req.http.host ~ .*");
        return (synth(200, "Full cache cleared"));
    }
    set req.backend_hint = cluster.backend();
}

sub vcl_deliver {
    unset resp.http.X-Varnish;
    if (obj.hits>0) {
        set resp.http.X-Cache = "HIT via " + server.ip;
    } else {
        set resp.http.X-Cache = "MISS from " + server.ip;
    }
}
