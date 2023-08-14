import unittest
import asyncio
import os
from dotenv import load_dotenv
from deepclient import DeepClient, DeepClientOptions
from gql import gql, Client
from gql.transport.aiohttp import AIOHTTPTransport


class TestDeepClientSelect(unittest.IsolatedAsyncioTestCase):
    @staticmethod
    def make_deep_client(token, url):
        if not token:
            raise ValueError("No token provided")
        if not url:
            raise ValueError("No url provided")
        transport = AIOHTTPTransport(url=url, headers={'Authorization': f"Bearer {token}"})
        client = Client(transport=transport, fetch_schema_from_transport=True)
        options = DeepClientOptions(gql_client=client)
        deep_client = DeepClient(options)
        return deep_client

    async def testSelect(self):
        load_dotenv()
        self.client = self.make_deep_client(os.getenv('BEARER_TOKEN'), os.getenv('URL_GQL', 'http://localhost:3006/gql'))
        print(await self.client.select(1))
