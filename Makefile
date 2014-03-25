all:
	 make -C src

backup:
	 cp -rf . /tmp/blocksyturvy
	 cd /tmp/blocksyturvy && make clean
	 cd /tmp && tar -zcf blocksyturvy-`date "+%Y.%m.%d.%H.%M.%S"`.tar.gz blocksyturvy
	 cd /tmp && rm -rf blocksyturvy
	 mv /tmp/blocksyturvy*.gz ../backup

clean:
	 make -C src clean

