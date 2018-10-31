import discord
from discord.ext import commands

bot = commands.Bot(command_prefix='!', description='A bot that matches leech buyers and sellers.')

@bot.event
async def on_ready():
    print('BotName:', bot.user.name)
    print('BotID:', bot.user.id)
    print('-------------------')

@bot.command()
async def greet(ctx):
    await ctx.send(':smiley: Hello there!')



@bot.command()
async def info(ctx):
    embedinfo = discord.Embed(title="nice bot", description="Nicest bot there is ever.", color=0xeee657)
    # give info about you here
    embedinfo.add_field(name="Author", value="<YOUR-USERNAME>")
    # Shows the number of servers the bot is member of.
    embedinfo.add_field(name="Server count", value=f"{len(bot.guilds)}")
    # give users a link to invite thsi bot to their server
    embedinfo.add_field(name="Invite", value="[Invite link](<insert your OAuth invitation link here>)")
    await ctx.send(embed=embedinfo)

bot.run('Token')
