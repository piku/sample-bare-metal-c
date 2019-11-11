A [Piku](https://piku.github.io/) deployment example which builds and deploys a server written in pure C.

To deploy this:

 * Clone this repository.
 * make sure you have gcc installed (`apt-get install build-essential`)
 * Push it up to your [Piku](https://piku.github.io/) box:

```shell
git remote add piku piku@your_server:baremetal
git push piku master
```

Then you can put it on the internet, assuming you have some domain pointing to the same machine:

```shell
piku config:set NGINX_SERVER_NAME=your_domain HTTPS_ONLY=1
```

After that you can browse to `https://your_domain/` and see the hello world message returned by the server.
