#!/bin/sh
echo Starting Codeforces Contest Wizard...
name=contest-wizard-starter-1.0-`date +%N`.jar
url=http://codeforces.org/s/31151/wizard/contest-wizard-starter-1.0-SNAPSHOT.jar?session=62b5ce1449d0a3c8378e099e4fb6e55a
cd $TEMP
wget --output-document=$name $url
java -cp $name -Xss5m -Xmx1024m com.codeforces.contestwizard.Main QUNQQyBTcHJpbmcgMjAyNSBXZWVrIDkgUHJhY3RpY2UgQ29udGVzdA \# NjA MTA1ODEwL3NhbmRib3gvY29udGVzdC56aXA KmpsYXNzXw a2dSSXhSRDBjRElvaDBxRk1tMU93RGNyV1MwVVNZMGxfLXBpa2JPQldZbkhRMXVDUQ ZW4 ZmFsc2U \# \# \# &
