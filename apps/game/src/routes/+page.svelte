<script lang="ts">
	import { Application, Sprite } from 'pixi.js';

	import {onMount} from 'svelte'

  onMount(() => {
		const app = new Application({ width: 640, height: 360 });
	
		// @ts-ignore
		document.getElementById('game')?.appendChild(app.view);

		let sprite = Sprite.from('sprites/ship.png');

		app.stage.addChild(sprite);

		let elapsed = 0.0;
		app.ticker.add((delta) => {
			elapsed += delta;
			sprite.x = 100.0 + Math.cos(elapsed/50.0) * 100.0;
		});
  })

</script>

<svelte:head>
	<title>Home</title>
	<meta name="description" content="Svelte demo app" />
</svelte:head>

<section>
	<h1>
		Hello PixiJS
	</h1>

	<div id='game' />
</section>